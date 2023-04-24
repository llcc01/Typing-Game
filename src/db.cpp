#include "db.hpp"


#include "utils/md5.h"


Database* Database::instance_ = nullptr;
std::mutex Database::mutex_;

Database& Database::GetInstance()
{
    if (instance_ == nullptr)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (instance_ == nullptr)
        {
            instance_ = new Database();
        }
    }
    return *instance_;
}

void Database::DestroyInstance()
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

uint64_t Database::AddUser(const std::string& username, const std::string& password, UserType type)
{
    std::string passwordHash = utils::md5(password);
    switch (type)
    {
    case UserType::Player:
    {
        Player player(username, passwordHash);
        return storage_.insert(player);
        break;
    }
    case UserType::Maker:
    {
        Maker maker(username, passwordHash);
        return storage_.insert(maker);
        break;
    }
    default:
        break;
    }

    return 0;
}

uint64_t Database::CheckUser(const std::string& username, const std::string& password, UserType type)
{
    std::string passwordHash = utils::md5(password);
    switch (type)
    {
    case UserType::Player:
    {
        auto players = storage_.get_all<Player>(orm::where(orm::is_equal(&Player::DBGetName, username)));
        if (players.size() > 0 && players[0].GetPasswordHash() == passwordHash)
        {
            return players[0].GetId();
        }
        else
        {
            return 0;
        }
        break;
    }
    case UserType::Maker:
    {
        auto makers = storage_.get_all<Maker>(orm::where(orm::is_equal(&Maker::DBGetName, username)));
        if (makers.size() > 0 && makers[0].GetPasswordHash() == passwordHash)
        {
            return makers[0].GetId();
        }
        else
        {
            return 0;
        }
        break;
    }
    default:
        break;
    }

    return 0;
}

namespace db
{

void FetchUsers(std::vector<Player>& records, int sort, bool asc)
{
    records.clear();
    switch (sort)
    {
    case 0:
        records = Database::GetInstance().GetAll<Player>(&Player::DBGetId, asc);
        break;
    case 1:
        records = Database::GetInstance().GetAll<Player>(&Player::DBGetName, asc);
        break;
    case 2:
        records = Database::GetInstance().GetAll<Player>(&Player::GetScore, asc);
        break;
    case 3:
        records = Database::GetInstance().GetAll<Player>(&Player::GetLevel, asc);
        break;
    case 4:
        records = Database::GetInstance().GetAll<Player>(&Player::GetPassNum, asc);
        break;
    default:
        break;
    }
}

void FetchUsers(std::vector<Maker>& records, int sort, bool asc)
{
    records.clear();
    switch (sort)
    {
    case 0:
        records = Database::GetInstance().GetAll<Maker>(&Maker::DBGetId, asc);
        break;
    case 1:
        records = Database::GetInstance().GetAll<Maker>(&Maker::DBGetName, asc);
        break;
    case 2:
        records = Database::GetInstance().GetAll<Maker>(&Maker::GetLevel, asc);
        break;
    case 3:
        records = Database::GetInstance().GetAll<Maker>(&Maker::GetQuesNum, asc);
        break;
    default:
        break;
    }
}

} // namespace db
