#pragma once

#ifndef __DB__
#define __DB__

#include <mutex>

#include <sqlite_orm/sqlite_orm.h>

#include "models/user.hpp"
#include "models/word.hpp"

namespace orm = sqlite_orm;

#define DB_MK_STR() orm::make_storage("db.sqlite",\
    orm::make_table("players",\
        orm::make_column("id", &Player::DBGetId, &Player::DBSetId, orm::primary_key().autoincrement()),\
        orm::make_column("name", &Player::DBGetName, &Player::DBSetName),\
        orm::make_column("password_hash", &Player::DBGetPasswordHash, &Player::DBSetPasswordHash),\
        orm::make_column("pass_num", &Player::GetPassNum, &Player::SetPassNum),\
        orm::make_column("score", &Player::GetScore, &Player::SetScore),\
        orm::make_column("level", &Player::GetLevel, &Player::SetLevel)\
    ),\
    orm::make_table("makers",\
        orm::make_column("id", &Maker::DBGetId, &Maker::DBSetId, orm::primary_key().autoincrement()),\
        orm::make_column("name", &Maker::DBGetName, &Maker::DBSetName),\
        orm::make_column("password_hash", &Maker::DBGetPasswordHash, &Maker::DBSetPasswordHash),\
        orm::make_column("ques_num", &Maker::GetQuesNum, &Maker::SetQuesNum),\
        orm::make_column("level", &Maker::GetLevel, &Maker::SetLevel)\
    ),\
    orm::make_table("words",\
        orm::make_column("id", &Word::GetId, &Word::SetId, orm::primary_key().autoincrement()),\
        orm::make_column("word", &Word::GetWord, &Word::SetWord, orm::unique()),\
        orm::make_column("level", &Word::GetLevel, &Word::SetLevel),\
        orm::make_column("maker_id", &Word::GetMakerId, &Word::SetMakerId)\
    )\
)

using Storage = decltype(DB_MK_STR());


class Database
{
private:
    Storage storage_ = DB_MK_STR();

private:
    Database() { storage_.sync_schema(); };
    ~Database() {};

    Database(const Database&);
    const Database& operator=(const Database&);

    static Database* instance_;
    static std::mutex mutex_;

public:
    Storage& GetStorage() { return storage_; };
    static Database& GetInstance();
    static void DestroyInstance();

    template <class T, class R>
    std::vector<T> GetAll(R funRef, bool asc = true) {
        return asc ?
            storage_.get_all<T>(orm::order_by(funRef).asc()) : storage_.get_all<T>(orm::order_by(funRef).desc());
    }

    template <class T, class R, class C>
    std::vector<T> GetAll(R funRef, C condition, bool asc = true) {
        return asc ?
            storage_.get_all<T>(orm::order_by(funRef).asc(), orm::where(condition)) : storage_.get_all<T>(orm::order_by(funRef).desc(), orm::where(condition));
    }

};

namespace db
{ 

uint64_t AddUser(const std::string& username, const std::string& password, UserRole type);
uint64_t CheckUser(const std::string& username, const std::string& password, UserRole type);

template <class T>
void GetUser(T& user, uint64_t id);

template <class T>
void UpdateUser(const T& user);

void FetchUsers(std::vector<Player>& records, int sort, bool asc, const std::vector<std::string>& filters);
void FetchUsers(std::vector<Maker>& records, int sort, bool asc, const std::vector<std::string>& filters);

void AddWord(const std::string& word, uint32_t level, uint64_t makerId);
void DeleteWord(uint64_t id);
void FetchWords(std::vector<Word>& records);
size_t GetRandomWords(std::vector<std::string>& records, uint32_t level, size_t num);

} // namespace db


#endif