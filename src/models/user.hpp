#ifndef __MODELS_USER__
#define __MODELS_USER__

#include <string>

enum class UserRole
{
    None,
    Player,
    Maker,
    Rank,
    Search
};

const std::string UserRoleStr[] = { "None", "Player", "Maker", "Rank", "Search" };

class User
{
private:
    uint64_t id_;
    std::string name_;
    std::string passwordHash_;
public:
    User() { id_ = 0; };
    User(uint64_t id) : id_(id) {};

    uint64_t GetId() const { return id_; };
    void SetId(uint64_t id) { id_ = id; };

    std::string GetName() const { return name_; };
    void SetName(const std::string& name) { name_ = name; };

    std::string GetPasswordHash() const { return passwordHash_; };
    void SetPasswordHash(const std::string& passwordHash) { passwordHash_ = passwordHash; };

    virtual void FromString(const std::string& str) = 0;
};

class ClientInfo
{
private:
    time_t lastActiveTime_; // 最后活跃时间
    std::string ip_;
    uint16_t port_;
public:
    ClientInfo() { lastActiveTime_ = 0; ip_ = ""; port_ = 0; };
    ClientInfo(const std::string& ip, uint16_t port) : ip_(ip), port_(port) {};

    time_t GetLastActiveTime() const { return lastActiveTime_; };
    void SetLastActiveTime(time_t lastActiveTime) { lastActiveTime_ = lastActiveTime; };

    std::string GetIp() const { return ip_; };
    void SetIp(const std::string& ip) { ip_ = ip; };

    uint16_t GetRxPort() const { return port_; };
    void SetRxPort(uint16_t port) { port_ = port; };
};

class Player : public User
{
private:
    uint16_t passNum_; // 通关数
    uint32_t score_; // 经验值
    uint32_t level_; // 等级
    ClientInfo clientInfo_; // 客户端信息
public:
    Player() { passNum_ = 0; score_ = 0; level_ = 0; };
    Player(uint64_t id) : User(id), passNum_(0), score_(0), level_(0) {};
    Player(const std::string& name, const std::string& passwordHash) : User(), passNum_(0), score_(0), level_(0)
    {
        SetName(name);
        SetPasswordHash(passwordHash);
    };

    // for orm
    uint64_t DBGetId() const { return GetId(); };
    void DBSetId(uint64_t id) { SetId(id); };
    std::string DBGetName() const { return GetName(); };
    void DBSetName(const std::string& name) { SetName(name); };
    std::string DBGetPasswordHash() const { return GetPasswordHash(); };
    void DBSetPasswordHash(const std::string& passwordHash) { SetPasswordHash(passwordHash); };

    uint16_t GetPassNum() const { return passNum_; };
    void SetPassNum(uint16_t passNum) { passNum_ = passNum; };

    uint32_t GetScore() const { return score_; };
    void SetScore(uint32_t score) { score_ = score; };

    uint32_t GetLevel() const { return level_; };
    void SetLevel(uint32_t level) { level_ = level; };

    time_t GetLastActiveTime() const { return clientInfo_.GetLastActiveTime(); };
    void SetLastActiveTime(time_t lastActiveTime) { clientInfo_.SetLastActiveTime(lastActiveTime); };

    std::string GetIp() const { return clientInfo_.GetIp(); };
    void SetIp(const std::string& ip) { clientInfo_.SetIp(ip); };

    uint16_t GetRxPort() const { return clientInfo_.GetRxPort(); };
    void SetRxPort(uint16_t port) { clientInfo_.SetRxPort(port); };

    void FromString(const std::string& str)
    {
        std::string::size_type pos = str.find('\t');
        SetId(std::stoull(str.substr(0, pos)));
        std::string::size_type pos2 = str.find('\t', pos + 1);
        SetName(str.substr(pos + 1, pos2 - pos - 1));
        std::string::size_type pos3 = str.find('\t', pos2 + 1);
        SetPasswordHash(str.substr(pos2 + 1, pos3 - pos2 - 1));
        std::string::size_type pos4 = str.find('\t', pos3 + 1);
        SetPassNum(std::stoi(str.substr(pos3 + 1, pos4 - pos3 - 1)));
        std::string::size_type pos5 = str.find('\t', pos4 + 1);
        SetScore(std::stoi(str.substr(pos4 + 1, pos5 - pos4 - 1)));
        std::string::size_type pos6 = str.find('\t', pos5 + 1);
        SetLevel(std::stoi(str.substr(pos5 + 1, pos6 - pos5 - 1)));
        std::string::size_type pos7 = str.find('\t', pos6 + 1);
        clientInfo_.SetLastActiveTime(std::stoi(str.substr(pos6 + 1, pos7 - pos6 - 1)));
        std::string::size_type pos8 = str.find('\t', pos7 + 1);
        clientInfo_.SetIp(str.substr(pos7 + 1, pos8 - pos7 - 1));
        clientInfo_.SetRxPort(std::stoi(str.substr(pos8 + 1)));
    };
    std::string ToString() const {
        return std::to_string(GetId()) + "\t"
            + GetName() + "\t"
            + GetPasswordHash()
            + "\t" + std::to_string(GetPassNum())
            + "\t" + std::to_string(GetScore())
            + "\t" + std::to_string(GetLevel())
            + "\t" + std::to_string(GetLastActiveTime())
            + "\t" + GetIp()
            + "\t" + std::to_string(GetRxPort())
            ;
    };

};

class Maker : public User
{
private:
    uint16_t quesNum_;
    uint32_t level_;
public:
    Maker() { quesNum_ = 0; level_ = 0; };
    Maker(uint64_t id) : User(id), quesNum_(0), level_(0) {};
    Maker(const std::string& name, const std::string& passwordHash) : User(), quesNum_(0), level_(0)
    {
        SetName(name);
        SetPasswordHash(passwordHash);
    };

    // for orm
    uint64_t DBGetId() const { return GetId(); };
    void DBSetId(uint64_t id) { SetId(id); };
    std::string DBGetName() const { return GetName(); };
    void DBSetName(const std::string& name) { SetName(name); };
    std::string DBGetPasswordHash() const { return GetPasswordHash(); };
    void DBSetPasswordHash(const std::string& passwordHash) { SetPasswordHash(passwordHash); };

    uint16_t GetQuesNum() const { return quesNum_; };
    void SetQuesNum(uint16_t quesNum) { quesNum_ = quesNum; };

    uint32_t GetLevel() const { return level_; };
    void SetLevel(uint32_t level) { level_ = level; };

    void FromString(const std::string& str)
    {
        std::string::size_type pos = str.find('\t');
        SetId(std::stoull(str.substr(0, pos)));
        std::string::size_type pos2 = str.find('\t', pos + 1);
        SetName(str.substr(pos + 1, pos2 - pos - 1));
        std::string::size_type pos3 = str.find('\t', pos2 + 1);
        SetPasswordHash(str.substr(pos2 + 1, pos3 - pos2 - 1));
        std::string::size_type pos4 = str.find('\t', pos3 + 1);
        SetQuesNum(std::stoi(str.substr(pos3 + 1, pos4 - pos3 - 1)));
        SetLevel(std::stoi(str.substr(pos4 + 1)));
    };
    std::string ToString() const { return std::to_string(GetId()) + "\t" + GetName() + "\t" + GetPasswordHash() + "\t" + std::to_string(GetQuesNum()) + "\t" + std::to_string(GetLevel()); };
};

#endif