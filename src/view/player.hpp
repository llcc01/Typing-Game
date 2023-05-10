#ifndef __VIEW_PLAYER__
#define __VIEW_PLAYER__

#include "view/ui.hpp"

#include "models/user.hpp"

namespace view::player
{

void Loop(ui::ScreenInteractive& screen, Player& player);
} // namespace view::player



#endif