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
};

class Player : public User
{
private:
    uint16_t passNum_; // 通关数
    uint32_t score_; // 经验值
    uint32_t level_; // 等级
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
};

#endif