#ifndef __VIEW_LOGIN__
#define __VIEW_LOGIN__

#include "view/ui.hpp"
#include "models/user.hpp"

namespace view::login
{

bool Loop(ui::ScreenInteractive& screen, uint64_t& uid, UserRole& urole, uint64_t& peerId);

} // namespace view::login




#endif