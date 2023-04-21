#ifndef __MODELS_USER_HPP__
#define __MODELS_USER_HPP__

#include <string>

class User
{
private:
    std::string name_;

public:
    User(const std::string& name): name_(name) {};
    ~User() {};
};

class Player: public User
{
private:
    uint16_t passNum_;
    uint32_t score_;
    uint32_t level_;
public:
    Player(const std::string& name): User(name), passNum_(0), score_(0), level_(0) {};
    ~Player() {};
};

class Maker: public User
{
private:
    uint16_t quesNum_;
    uint32_t level_;
public:
    Maker(const std::string& name): User(name), quesNum_(0), level_(0) {};
    ~Maker() {};
};

#endif