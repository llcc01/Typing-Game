#include "rpc/server.hpp"
#include <winsock2.h>
#include <thread>
#include <iostream>

#include "db.hpp"

namespace rpc::server
{

uint8_t response(const SOCKET& clientSocket, const std::string& res)
{
    send(clientSocket, res.c_str(), res.size() + 1, 0);
    return 0;
}

std::string getParam(const std::string& req, const std::string& paramName)
{
    std::string::size_type pos = req.find(paramName + "=");
    if (pos != std::string::npos)
    {
        std::string value = req.substr(pos + paramName.size() + 1, req.find("&", pos) - pos - paramName.size() - 1);
        std::cout << "getParam: " << paramName << "=" << value << std::endl;
        return value;
    }
    return "";
}


void addUser(const std::string& req, std::string& res)
{
    std::string username = getParam(req, "username");
    std::string password = getParam(req, "password");
    std::string type = getParam(req, "type");
    uint64_t id = 0;
    if (type == "Player")
    {
        id = db::AddUser(username, password, UserRole::Player);
    }
    else if (type == "Maker")
    {
        id = db::AddUser(username, password, UserRole::Maker);
    }
    res = std::to_string(id);

}

void checkUser(const std::string& req, std::string& res)
{
    std::string username = getParam(req, "username");
    std::string password = getParam(req, "password");
    std::string type = getParam(req, "type");
    uint64_t id = 0;
    if (type == "Player")
    {
        id = db::CheckUser(username, password, UserRole::Player);
    }
    else if (type == "Maker")
    {
        id = db::CheckUser(username, password, UserRole::Maker);
    }
    res = std::to_string(id);
}

void getUser(const std::string& req, std::string& res)
{
    std::string id = getParam(req, "id");
    std::string type = getParam(req, "type");
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

void updateUser(const std::string& req, std::string& res)
{
    std::string id = getParam(req, "id");
    std::string name = getParam(req, "name");
    std::string passwordHash = getParam(req, "passwordHash");
    std::string type = getParam(req, "type");
    if (type == "Player")
    {
        Player player;
        player.SetId(std::stoull(id));
        player.SetName(name);
        player.SetPasswordHash(passwordHash);
        player.SetPassNum(std::stoi(getParam(req, "passNum")));
        player.SetScore(std::stoi(getParam(req, "score")));
        player.SetLevel(std::stoi(getParam(req, "level")));
        db::UpdateUser(player);
    }
    else if (type == "Maker")
    {
        Maker maker;
        maker.SetId(std::stoull(id));
        maker.SetName(name);
        maker.SetPasswordHash(passwordHash);
        maker.SetQuesNum(std::stoi(getParam(req, "quesNum")));
        maker.SetLevel(std::stoi(getParam(req, "level")));
        db::UpdateUser(maker);
    }
}

void fetchUsers(const std::string& req, std::string& res)
{
    std::string type = getParam(req, "type");
    std::string sort = getParam(req, "sort");
    std::string asc = getParam(req, "asc");
    std::string filtersStr = getParam(req, "filters");
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

void addWord(const std::string& req, std::string& res)
{
    std::string word = getParam(req, "word");
    std::string level = getParam(req, "level");
    std::string makerId = getParam(req, "makerId");
    db::AddWord(word, std::stoi(level), std::stoull(makerId));
}

void deleteWord(const std::string& req, std::string& res)
{
    std::string id = getParam(req, "id");
    db::DeleteWord(std::stoull(id));
}

void fetchWords(const std::string& req, std::string& res)
{
    std::vector<Word> records;
    db::FetchWords(records);
    for (auto& record : records)
    {
        res += record.ToString() + "\n";
    }
}

void getRandomWords(const std::string& req, std::string& res)
{
    std::string level = getParam(req, "level");
    std::string num = getParam(req, "num");
    std::vector<std::string> records;
    db::GetRandomWords(records, std::stoi(level), std::stoi(num));
    for (auto& record : records)
    {
        res += record + "\n";
    }
}


void handle(const SOCKET clientSocket)
{
    std::string req;
    while (true)
    {
        char recvdata[256];
        int num = recv(clientSocket, recvdata, 256, 0);
        if (num > 0) {
            req += std::string(recvdata, num);
            if (recvdata[num - 1] == '\0')
            {
                break;
            }
        }
    }
    std::string res;
    std::cout << "req: " << req << std::endl;
    std::string action = req.substr(0, req.find("?"));
    if (action == "AddUser")
    {
        addUser(req, res);
    }
    else if (action == "CheckUser")
    {
        checkUser(req, res);
    }
    else if (action == "GetUser")
    {
        getUser(req, res);
    }
    else if (action == "UpdateUser")
    {
        updateUser(req, res);
    }
    else if (action == "FetchUsers")
    {
        fetchUsers(req, res);
    }
    else if (action == "AddWord")
    {
        addWord(req, res);
    }
    else if (action == "DeleteWord")
    {
        deleteWord(req, res);
    }
    else if (action == "FetchWords")
    {
        fetchWords(req, res);
    }
    else if (action == "GetRandomWords")
    {
        getRandomWords(req, res);
    }
    else
    {
        res = "";
        std::cout << "Unknown action: " << action << std::endl;
    }

    std::cout << "res: " <<res << std::endl;
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
        std::thread(handle, clientSocket).detach();
    }
    closesocket(serverSocket);
    return 0;
}

} // namespace rpc::server


