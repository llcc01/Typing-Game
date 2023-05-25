#ifndef __RPC_CLIENT__
#define __RPC_CLIENT__

#include <stdint.h>
#include <string>
#include <vector>
#include <mutex>
#include "models/user.hpp"
#include "models/word.hpp"

namespace rpc::client::db
{

uint64_t AddUser(const std::string& username, const std::string& password, UserRole type);
uint64_t CheckUser(const std::string& username, const std::string& password, UserRole type);

template <class T>
void GetUser(T& user, uint64_t id);

void UpdateUser(const Player& user);
void UpdateUser(const Maker& user);

void FetchUsers(std::vector<Player>& records, int sort, bool asc, const std::vector<std::string>& filters);
void FetchUsers(std::vector<Maker>& records, int sort, bool asc, const std::vector<std::string>& filters);

void AddWord(const std::string& word, uint32_t level, uint64_t makerId);
void DeleteWord(uint64_t id);
void FetchWords(std::vector<Word>& records);
size_t GetRandomWords(std::vector<std::string>& records, uint32_t level, size_t num);

} // namespace db

namespace rpc::client
{
class Session
{
private:
    UserRole role_ = UserRole::None;
    uint64_t uid_ = 0;

private:
    Session() {}
    ~Session() {}
    Session(const Session&);
    const Session& operator=(const Session&);

    static Session* instance_;
    static std::mutex mutex_;

public:
    static Session& GetInstance();
    static void DestroyInstance();

    static void Start(UserRole role, uint64_t uid)
    {
        Session& session = GetInstance();
        session.role_ = role;
        session.uid_ = uid;
    }

    static void End()
    {
        Session& session = GetInstance();
        session.role_ = UserRole::None;
        session.uid_ = 0;
    }

    static uint64_t GetUid()
    {
        Session& session = GetInstance();
        return session.uid_;
    }

    static UserRole GetRole()
    {
        Session& session = GetInstance();
        return session.role_;
    }
};

} // namespace rpc::client


#endif