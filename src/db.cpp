#include "db.hpp"


#include "utils/md5.h"

const std::string PASSWORD_SALT = "typing-game-2023";

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

namespace db
{

inline std::string getPasswordHash(const std::string& password)
{
    return utils::md5(utils::md5(password) + PASSWORD_SALT);
}

uint64_t AddUser(const std::string& username, const std::string& password, UserRole type)
{
    std::string passwordHash = getPasswordHash(password);
    switch (type)
    {
    case UserRole::Player:
    {
        Player player(username, passwordHash);
        return Database::GetInstance().GetStorage().insert(player);
        break;
    }
    case UserRole::Maker:
    {
        Maker maker(username, passwordHash);
        return Database::GetInstance().GetStorage().insert(maker);
        break;
    }
    default:
        break;
    }

    return 0;
}

uint64_t CheckUser(const std::string& username, const std::string& password, UserRole type)
{
    std::string passwordHash = getPasswordHash(password);
    switch (type)
    {
    case UserRole::Player:
    {
        auto players = Database::GetInstance().GetStorage().get_all<Player>(orm::where(orm::is_equal(&Player::DBGetName, username)));
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
    case UserRole::Maker:
    {
        auto makers = Database::GetInstance().GetStorage().get_all<Maker>(orm::where(orm::is_equal(&Maker::DBGetName, username)));
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

template <class T>
void GetUser(T& user, uint64_t id)
{
    auto users = Database::GetInstance().GetStorage().get_all<T>(orm::where(orm::is_equal(&T::DBGetId, id)));
    if (users.size() > 0)
    {
        user = users[0];
    }
}

template void GetUser(Player& user, uint64_t id);
template void GetUser(Maker& user, uint64_t id);

template <class T>
void UpdateUser(const T& player)
{
    Database::GetInstance().GetStorage().update(player);
}

template void UpdateUser(const Player& player);
template void UpdateUser(const Maker& player);

void FetchUsers(std::vector<Player>& records, int sort, bool asc, const std::vector<std::string>& filters)
{
    records.clear();

    uint64_t uid = 0;
    std::string name = "";
    uint32_t score = 0;
    uint32_t level = 0;
    uint32_t passNum = 0;
    try
    {
        if (filters[0] != "")
        {
            uid = std::stoull(filters[0]);
        }
        if (filters[1] != "")
        {
            name = filters[1];
        }
        if (filters[2] != "")
        {
            score = std::stoul(filters[2]);
        }
        if (filters[3] != "")
        {
            level = std::stoul(filters[3]);
        }
        if (filters[4] != "")
        {
            passNum = std::stoul(filters[4]);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }

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

    for (auto it = records.begin(); it != records.end();)
    {
        if (filters[0] != "" && it->GetId() != uid)
        {
            it = records.erase(it);
            continue;
        }
        if (filters[1] != "" && it->GetName().find(name) == std::string::npos)
        {
            it = records.erase(it);
            continue;
        }
        if (filters[2] != "" && it->GetScore() != score)
        {
            it = records.erase(it);
            continue;
        }
        if (filters[3] != "" && it->GetLevel() != level)
        {
            it = records.erase(it);
            continue;
        }
        if (filters[4] != "" && it->GetPassNum() != passNum)
        {
            it = records.erase(it);
            continue;
        }
        ++it;
    }
}

void FetchUsers(std::vector<Maker>& records, int sort, bool asc, const std::vector<std::string>& filters)
{
    records.clear();

    uint64_t uid = 0;
    std::string name = "";
    uint32_t level = 0;
    uint32_t quesNum = 0;
    try
    {
        if (filters[0] != "")
        {
            uid = std::stoull(filters[0]);
        }
        if (filters[1] != "")
        {
            name = filters[1];
        }
        if (filters[2] != "")
        {
            level = std::stoul(filters[2]);
        }
        if (filters[3] != "")
        {
            quesNum = std::stoul(filters[3]);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return;
    }

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

    for (auto it = records.begin(); it != records.end();)
    {
        if (filters[0] != "" && it->GetId() != uid)
        {
            it = records.erase(it);
            continue;
        }
        if (filters[1] != "" && it->GetName().find(name) == std::string::npos)
        {
            it = records.erase(it);
            continue;
        }
        if (filters[2] != "" && it->GetLevel() != level)
        {
            it = records.erase(it);
            continue;
        }
        if (filters[3] != "" && it->GetQuesNum() != quesNum)
        {
            it = records.erase(it);
            continue;
        }
        ++it;
    }
}

void AddWord(const std::string& word, uint32_t level, uint64_t makerId)
{
    Word newWord(word, level, makerId);
    Database::GetInstance().GetStorage().insert(newWord);
}

void DeleteWord(uint64_t id)
{
    Database::GetInstance().GetStorage().remove<Word>(id);
}

void FetchWords(std::vector<Word>& records)
{
    records.clear();
    records = Database::GetInstance().GetAll<Word>(&Word::GetWord, true);
}

size_t GetRandomWords(std::vector<std::string>& records, uint32_t level, size_t num)
{
    records.clear();
    auto words = Database::GetInstance().GetStorage().get_all<Word>(orm::where(orm::is_equal(&Word::GetLevel, level)), orm::order_by(sqlite_orm::random()), orm::limit(num));
    for (auto& word : words)
    {
        records.push_back(word.GetWord());
    }
    return words.size();
}

} // namespace db
