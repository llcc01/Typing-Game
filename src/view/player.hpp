#ifndef __VIEW_PLAYER__
#define __VIEW_PLAYER__

#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include <ftxui/component/screen_interactive.hpp>
#include "ftxui/component/captured_mouse.hpp"

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, separator, Element, operator|, vbox, border
#include "ftxui/util/ref.hpp"  // for Ref

namespace ui = ftxui;

namespace view::player
{

    void Loop(ui::ScreenInteractive& screen);
} // namespace view::player



#endif