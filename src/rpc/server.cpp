#include "rpc/server.hpp"
#include <winsock2.h>
#include <thread>
#include <iostream>
#include <map>

#include "db.hpp"
#include "rpc/rpc.hpp"

namespace rpc::server
{

uint8_t response(const SOCKET& clientSocket, const std::string& res)
{
    send(clientSocket, res.c_str(), res.size() + 1, 0);
    return 0;
}

void addUser(const Request& req, std::string& res)
{
    std::string username = req.GetParam("username");
    std::string password = req.GetParam("password");
    std::string type = req.GetParam("type");
    uint64_t id = 0;
    try
    {
        if (type == "Player")
        {
            id = db::AddUser(username, password, UserRole::Player);
        }
        else if (type == "Maker")
        {
            id = db::AddUser(username, password, UserRole::Maker);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    res = std::to_string(id);
}

void checkUser(const Request& req, std::string& res)
{
    std::string username = req.GetParam("username");
    std::string password = req.GetParam("password");
    std::string type = req.GetParam("type");
    uint64_t id = 0;
    if (type == "Player")
    {
        id = db::CheckUser(username, password, UserRole::Player);
    }
    else if (type == "Maker")
    {
        id = db::CheckUser(username, password, UserRole::Maker);
    }
    else
    {
        std::cout << "Unknown user type: " << type << std::endl;
    }
    res = std::to_string(id);
}

void getUser(const Request& req, std::string& res)
{
    std::string id = req.GetParam("id");
    std::string type = req.GetParam("type");
    if (type == "Player")
    {
        Player player;
        db::GetUser(player, std::stoull(id));
        res = player.ToString();
    }
    else if (type == "Maker")
    {
        Maker maker;
        db::GetUser(maker, std::stoull(id));
        res = maker.ToString();
    }
}

void updateUser(const Request& req, std::string& res)
{
    std::string id = req.GetParam("id");
    std::string name = req.GetParam("name");
    std::string passwordHash = req.GetParam("passwordHash");
    std::string type = req.GetParam("type");
    if (type == "Player")
    {
        Player player;
        db::GetUser(player, std::stoull(id));
        player.SetName(name);
        player.SetPasswordHash(passwordHash);
        player.SetPassNum(std::stoi(req.GetParam("passNum")));
        player.SetScore(std::stoi(req.GetParam("score")));
        player.SetLevel(std::stoi(req.GetParam("level")));
        player.SetRxPort(std::stoi(req.GetParam("port")));
        db::UpdateUser(player);
    }
    else if (type == "Maker")
    {
        Maker maker;
        maker.SetId(std::stoull(id));
        maker.SetName(name);
        maker.SetPasswordHash(passwordHash);
        maker.SetQuesNum(std::stoi(req.GetParam("quesNum")));
        maker.SetLevel(std::stoi(req.GetParam("level")));
        db::UpdateUser(maker);
    }
}

void fetchUsers(const Request& req, std::string& res)
{
    std::string type = req.GetParam("type");
    std::string sort = req.GetParam("sort");
    std::string asc = req.GetParam("asc");
    std::string filtersStr = req.GetParam("filters");
    std::vector<std::string> filters;
    while (true)
    {
        std::string::size_type pos = filtersStr.find(',');
        if (pos == std::string::npos)
        {
            filters.push_back(filtersStr);
            break;
        }
        filters.push_back(filtersStr.substr(0, pos));
        filtersStr = filtersStr.substr(pos + 1);
    }
    if (type == "Player")
    {
        std::vector<Player> records;
        db::FetchUsers(records, std::stoi(sort), std::stoi(asc), filters);
        for (auto& record : records)
        {
            res += record.ToString() + "\n";
        }
    }
    else if (type == "Maker")
    {
        std::vector<Maker> records;
        db::FetchUsers(records, std::stoi(sort), std::stoi(asc), filters);
        for (auto& record : records)
        {
            res += record.ToString() + "\n";
        }
    }
}

void addWord(const Request& req, std::string& res)
{
    std::string word = req.GetParam("word");
    std::string level = req.GetParam("level");
    std::string makerId = req.GetParam("makerId");
    try
    {
        db::AddWord(word, std::stoi(level), std::stoull(makerId));
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        res = e.what();
    }
}

void deleteWord(const Request& req, std::string& res)
{
    std::string id = req.GetParam("id");
    db::DeleteWord(std::stoull(id));
}

void fetchWords(const Request& req, std::string& res)
{
    std::vector<Word> records;
    db::FetchWords(records);
    for (auto& record : records)
    {
        res += record.ToString() + "\n";
    }
}

void getRandomWords(const Request& req, std::string& res)
{
    std::string level = req.GetParam("level");
    std::string num = req.GetParam("num");
    std::vector<std::string> records;
    db::GetRandomWords(records, std::stoi(level), std::stoi(num));
    for (auto& record : records)
    {
        res += record + "\n";
    }
}

const std::map<std::string, std::function<void(const Request&, std::string&)>> ACTION_MAP = {
    {"AddUser",addUser},
    {"CheckUser",checkUser},
    {"GetUser",getUser},
    {"UpdateUser",updateUser},
    {"FetchUsers",fetchUsers},
    {"AddWord",addWord},
    {"DeleteWord",deleteWord},
    {"FetchWords",fetchWords},
    {"GetRandomWords",getRandomWords}
};

void handle(const SOCKET clientSocket, const sockaddr_in clientAddr)
{
    std::string reqStr;
    while (true)
    {
        char recvdata[256];
        int num = recv(clientSocket, recvdata, 256, 0);
        if (num > 0)
        {
            if (recvdata[num - 1] == '\0')
            {
                reqStr += std::string(recvdata, num - 1);
                break;
            }
            reqStr += std::string(recvdata, num);
        }
    }
    std::string res;
    std::cout << "reqStr: " << reqStr << std::endl;
    size_t pos1 = reqStr.find("\n");
    std::string cmd = reqStr.substr(0, pos1);
    std::string action = cmd.substr(0, cmd.find("?"));

    uint64_t id = 0;
    UserRole role = UserRole::None;

    size_t pos2 = reqStr.find("\n", pos1 + 1);
    if (pos2 != std::string::npos)
    {
        std::string auth = reqStr.substr(pos1 + 1, pos2 - pos1 - 1);
        size_t pos3 = auth.find(":");

        if (pos3 != std::string::npos)
        {
            role = static_cast<UserRole>(std::stoi(auth.substr(0, pos3)));
            id = std::stoull(auth.substr(pos3 + 1));
            if (role == UserRole::Player)
            {
                Player p;
                db::GetUser(p, id);
                p.SetLastActiveTime(time(nullptr));
                p.SetIp(inet_ntoa(clientAddr.sin_addr));
                db::UpdateUser(p);
            }

        }
    }

    Request req(cmd, role, id);
    auto fun = ACTION_MAP.find(action);
    if (fun != ACTION_MAP.end())
    {
        fun->second(req, res);
    }
    else
    {
        std::cout << "action not found: " << action << std::endl;
        res = "";
    }

    std::cout << "res: " << res << std::endl;
    response(clientSocket, res);
    closesocket(clientSocket);
}

uint8_t ServeForever(const std::string& ipAdrr, uint16_t port)
{
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        return 1;
    }
    sockaddr_in sock_in;
    sock_in.sin_family = AF_INET;
    sock_in.sin_port = htons(port);
    sock_in.sin_addr.S_un.S_addr = inet_addr(ipAdrr.c_str());
    if (bind(serverSocket, (sockaddr*)&sock_in, sizeof(sock_in)) == SOCKET_ERROR) {
        return 2;
    }
    if (listen(serverSocket, 5) == SOCKET_ERROR) {
        return 3;
    }
    std::cout << "Server is running at " << ipAdrr << ":" << port << std::endl;
    while (true)
    {
        sockaddr_in clientAddr;
        int len = sizeof(clientAddr);
        SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &len);
        if (clientSocket == INVALID_SOCKET) {
            continue;
        }
        std::cout << "New connection from " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << std::endl;
        std::thread(handle, clientSocket, clientAddr).detach();
    }
    closesocket(serverSocket);
    return 0;
}

} // namespace rpc::server


