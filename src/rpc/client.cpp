#include "rpc/client.hpp"
#include <winsock2.h>
#include <mutex>
// #pragma comment(lib,"ws2_32.lib")

const std::string IP_ADDR = "127.0.0.1";
const uint16_t PORT = 12345;

namespace rpc::client
{

Session* Session::instance_ = nullptr;
std::mutex Session::mutex_;

Session& Session::GetInstance()
{
    if (instance_ == nullptr)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance_ == nullptr)
        {
            instance_ = new Session();
        }
    }
    return *instance_;
}

void Session::DestroyInstance()
{
    if (instance_ != nullptr)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance_ != nullptr)
        {
            delete instance_;
            instance_ = nullptr;
        }
    }
}


uint8_t request(const std::string& ipAdrr, uint16_t port, const std::string& cmd, std::string& res)
{
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        return 1;
    }
    sockaddr_in sock_in;
    sock_in.sin_family = AF_INET;
    sock_in.sin_port = htons(port);
    sock_in.sin_addr.S_un.S_addr = inet_addr(ipAdrr.c_str());
    if (connect(clientSocket, (sockaddr*)&sock_in, sizeof(sock_in)) == SOCKET_ERROR) {
        return 1;
    }

    std::string reqStr = cmd + "\n" + std::to_string(uint16_t(Session::GetRole())) + ":" + std::to_string(Session::GetUid()) + "\n";

    send(clientSocket, reqStr.c_str(), reqStr.size() + 1, 0);

    while (true)
    {
        char recvdata[256];
        int num = recv(clientSocket, recvdata, 256, 0);
        if (num > 0) {
            if (recvdata[num - 1] == '\0')
            {
                res += std::string(recvdata, num - 1);
                break;
            }
            res += std::string(recvdata, num);
        }
    }
    closesocket(clientSocket);
    return 0;
}

namespace db
{

uint64_t AddUser(const std::string& username, const std::string& password, UserRole type)
{
    std::string req = "AddUser?username=" + username + "&password=" + password + "&type=" + UserRoleStr[uint16_t(type)];
    std::string res;
    request(IP_ADDR, PORT, req, res);
    return std::stoull(res);
}

uint64_t CheckUser(const std::string& username, const std::string& password, UserRole type)
{
    std::string req = "CheckUser?username=" + username + "&password=" + password + "&type=" + UserRoleStr[uint16_t(type)];
    std::string res;
    request(IP_ADDR, PORT, req, res);
    return std::stoull(res);
}

template <class T>
void GetUser(T& user, uint64_t id)
{
    std::string req = "GetUser?id=" + std::to_string(id) + "&type=" + UserRoleStr[uint16_t(UserRole::Player)];
    std::string res;
    request(IP_ADDR, PORT, req, res);
    user.FromString(res);
}

template void GetUser(Player& user, uint64_t id);
template void GetUser(Maker& user, uint64_t id);

void UpdateUser(const Player& user)
{
    std::string req = "UpdateUser?type=Player&id=" + std::to_string(user.GetId()) + "&name=" + user.GetName() + "&passwordHash="
        + user.GetPasswordHash() + "&passNum=" + std::to_string(user.GetPassNum()) + "&score=" + std::to_string(user.GetScore())
        + "&level=" + std::to_string(user.GetLevel());
    std::string res;
    request(IP_ADDR, PORT, req, res);
}

void UpdateUser(const Maker& user)
{
    std::string req = "UpdateUser?type=Maker&id=" + std::to_string(user.GetId()) + "&name=" + user.GetName() + "&passwordHash="
        + user.GetPasswordHash() + "&level=" + std::to_string(user.GetLevel()) + "&quesNum=" + std::to_string(user.GetQuesNum());
    std::string res;
    request(IP_ADDR, PORT, req, res);
}

void FetchUsers(std::vector<Player>& records, int sort, bool asc, const std::vector<std::string>& filters)
{
    records.clear();
    std::string req = "FetchUsers?type=Player&sort=" + std::to_string(sort) + "&asc=" + std::to_string(asc) + "&filters=";
    for (auto& filter : filters)
    {
        req += filter + ",";
    }
    std::string res;
    request(IP_ADDR, PORT, req, res);
    std::vector<std::string> recordsStr;
    while (true)
    {
        std::string::size_type pos = res.find('\n');
        if (pos == std::string::npos)
        {
            break;
        }
        recordsStr.push_back(res.substr(0, pos));
        res = res.substr(pos + 1);
    }
    Player player;
    for (auto& recordStr : recordsStr)
    {
        player.FromString(recordStr);
        records.push_back(player);
    }
}

void FetchUsers(std::vector<Maker>& records, int sort, bool asc, const std::vector<std::string>& filters)
{
    records.clear();
    std::string req = "FetchUsers?type=Maker&sort=" + std::to_string(sort) + "&asc=" + std::to_string(asc) + "&filters=";
    for (auto& filter : filters)
    {
        req += filter + ",";
    }
    std::string res;
    request(IP_ADDR, PORT, req, res);
    std::vector<std::string> recordsStr;
    while (true)
    {
        std::string::size_type pos = res.find('\n');
        if (pos == std::string::npos)
        {
            break;
        }
        recordsStr.push_back(res.substr(0, pos));
        res = res.substr(pos + 1);
    }
    Maker maker;
    for (auto& recordStr : recordsStr)
    {
        maker.FromString(recordStr);
        records.push_back(maker);
    }
}

void AddWord(const std::string& word, uint32_t level, uint64_t makerId)
{
    std::string req = "AddWord?word=" + word + "&level=" + std::to_string(level) + "&makerId=" + std::to_string(makerId);
    std::string res;
    request(IP_ADDR, PORT, req, res);
}

void DeleteWord(uint64_t id)
{
    std::string req = "DeleteWord?id=" + std::to_string(id);
    std::string res;
    request(IP_ADDR, PORT, req, res);
}

void FetchWords(std::vector<Word>& records)
{
    std::string req = "FetchWords";
    std::string res;
    request(IP_ADDR, PORT, req, res);
    std::vector<std::string> recordsStr;
    while (true)
    {
        std::string::size_type pos = res.find('\n');
        if (pos == std::string::npos)
        {
            break;
        }
        recordsStr.push_back(res.substr(0, pos));
        res = res.substr(pos + 1);
    }
    Word word;
    for (auto& recordStr : recordsStr)
    {
        word.FromString(recordStr);
        records.push_back(word);
    }
}

size_t GetRandomWords(std::vector<std::string>& records, uint32_t level, size_t num)
{
    records.clear();
    std::string req = "GetRandomWords?level=" + std::to_string(level) + "&num=" + std::to_string(num);
    std::string res;
    request(IP_ADDR, PORT, req, res);
    std::vector<std::string> recordsStr;
    while (true)
    {
        std::string::size_type pos = res.find('\n');
        if (pos == std::string::npos)
        {
            break;
        }
        recordsStr.push_back(res.substr(0, pos));
        res = res.substr(pos + 1);
    }
    for (auto& recordStr : recordsStr)
    {
        records.push_back(recordStr);
    }
    return records.size();
}

} // namespace db


} // namespace rpc::client


