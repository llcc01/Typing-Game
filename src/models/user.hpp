#ifndef __MODELS_USER__
#define __MODELS_USER__

#include <string>

class User
{
private:
    std::string name_;
    uint64_t id_;
public:
    User(uint64_t id): id_(id) {};
    ~User() {};

    uint64_t GetId() { return id_; };
    void SetId(uint64_t id) { id_ = id; };

    std::string GetName() { return name_; };
    void SetName(const std::string& name) { name_ = name; };
};

class Player: public User
{
private:
    uint16_t passNum_;
    uint32_t score_;
    uint32_t level_;
public:
    Player(uint64_t id): User(id), passNum_(0), score_(0), level_(0) {};
    ~Player() {};

    uint16_t GetPassNum() { return passNum_; };
    void SetPassNum(uint16_t passNum) { passNum_ = passNum; };

    uint32_t GetScore() { return score_; };
    void SetScore(uint32_t score) { score_ = score; };

    uint32_t GetLevel() { return level_; };
    void SetLevel(uint32_t level) { level_ = level; };
};

class Maker: public User
{
private:
    uint16_t quesNum_;
    uint32_t level_;
public:
    Maker(uint64_t id): User(id), quesNum_(0), level_(0) {};
    ~Maker() {};

    uint16_t GetQuesNum() { return quesNum_; };
    void SetQuesNum(uint16_t quesNum) { quesNum_ = quesNum; };

    uint32_t GetLevel() { return level_; };
    void SetLevel(uint32_t level) { level_ = level; };
};

#endif