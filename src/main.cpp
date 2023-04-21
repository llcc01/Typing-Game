#include <iostream>


#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/screen.hpp"
#include "ftxui/screen/string.hpp"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>

#include "db.hpp"
#include "view/player.hpp"

int main(void)
{
    auto screen = ftxui::ScreenInteractive::Fullscreen();

    view::player::Loop(screen);

    return EXIT_SUCCESS;
}
