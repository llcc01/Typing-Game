#pragma once

#ifndef __DB__
#define __DB__

#include <sqlite_orm/sqlite_orm.h>

#include "models/user.hpp"

#define DB_MK_STR() sqlite_orm::make_storage("db.sqlite",\
    sqlite_orm::make_table("players",\
        sqlite_orm::make_column("id", &Player::GetId, &Player::SetId, sqlite_orm::primary_key().autoincrement()),\
        sqlite_orm::make_column("name", &Player::GetName, &Player::SetName),\
        sqlite_orm::make_column("pass_num", &Player::GetPassNum, &Player::SetPassNum),\
        sqlite_orm::make_column("score", &Player::GetScore, &Player::SetScore),\
        sqlite_orm::make_column("level", &Player::GetLevel, &Player::SetLevel)\
    ),\
    sqlite_orm::make_table("makers",\
        sqlite_orm::make_column("id", &Maker::GetId, &Maker::SetId, sqlite_orm::primary_key().autoincrement()),\
        sqlite_orm::make_column("name", &Maker::GetName, &Maker::SetName),\
        sqlite_orm::make_column("ques_num", &Maker::GetQuesNum, &Maker::SetQuesNum),\
        sqlite_orm::make_column("level", &Maker::GetLevel, &Maker::SetLevel)\
    )\
)

namespace db
{

} // namespace db


#endif