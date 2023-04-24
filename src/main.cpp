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


int main(void)
{
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    Player player(0);
    view::player::Loop(screen, player);
    view::login::Loop(screen);

    view::rank::Loop(screen);

    Database::DestroyInstance();

    return EXIT_SUCCESS;
}
