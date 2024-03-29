#include <iostream>
#include <cassert>

#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/screen/string.hpp"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>

// #include "db.hpp"
#include "rpc/rpc.hpp"
#include "rpc/client.hpp"
#include "models/user.hpp"
#include "view/player.hpp"
#include "view/login.hpp"
#include "view/rank.hpp"
#include "view/maker.hpp"

using namespace rpc::client;

int main(void)
{
    if (rpc::Setup())
    {
        std::cout << "rpc::Setup() failed" << std::endl;
        return 1;
    }
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    // view::player::Loop(screen, player);
    uint64_t uid = 0;
    uint64_t peerId = 0;
    UserRole urole = UserRole::None;
    // while (1)
    // {
    //     uid = 1;
    //     peerId = 2;
    //     Player player;
    //     db::GetUser(player, uid);
    //     view::player::Loop(screen, player, peerId);
    //     db::UpdateUser(player);
    // }

    while (view::login::Loop(screen, uid, urole, peerId))
    {
        Session::Start(urole, uid);
        switch (urole)
        {
        case UserRole::Player:
        {
            Player player;
            db::GetUser(player, uid);
            view::player::Loop(screen, player, peerId);
            db::UpdateUser(player);
            peerId = 0;
            break;
        }
        case UserRole::Maker:
        {
            Maker maker(uid);
            db::GetUser(maker, uid);
            view::maker::Loop(screen, maker);
            db::UpdateUser(maker);
            peerId = 0;
            break;
        }
        case UserRole::Rank:
        {
            peerId = view::rank::Loop(screen);
            break;
        }

        default:
            peerId = 0;
            break;
        }
        Session::End();
    }


    // view::rank::Loop(screen);
    // view::maker::Loop(screen, user);

    // Database::DestroyInstance();
    Session::DestroyInstance();

    return EXIT_SUCCESS;
}
