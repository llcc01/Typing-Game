#include <iostream>
#include <cassert>

#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/screen/string.hpp"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>

#include "db.hpp"
#include "models/user.hpp"
#include "view/player.hpp"
#include "view/login.hpp"
#include "view/rank.hpp"
#include "view/maker.hpp"


int main(void)
{
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    // view::player::Loop(screen, player);
    uint64_t uid = 0;
    UserRole urole = UserRole::None;
    while (view::login::Loop(screen, uid, urole))
    {
        switch (urole)
        {
        case UserRole::Player:
        {
            Player player;
            db::GetUser(player, uid);
            view::player::Loop(screen, player);
            db::UpdateUser(player);
            break;
        }
        case UserRole::Maker:
        {
            Maker maker(uid);
            db::GetUser(maker, uid);
            view::maker::Loop(screen, maker);
            db::UpdateUser(maker);
            break;
        }
        case UserRole::Rank:
        {
            view::rank::Loop(screen);
            break;
        }

        default:
            break;
        }
    }


    // view::rank::Loop(screen);
    // view::maker::Loop(screen, user);

    Database::DestroyInstance();

    return EXIT_SUCCESS;
}
