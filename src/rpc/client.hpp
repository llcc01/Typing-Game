#ifndef __RPC_CLIENT__
#define __RPC_CLIENT__

#include <stdint.h>
#include <string>
#include <vector>
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



#endif