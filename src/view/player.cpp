#include "view/player.hpp"
#include <iostream>
#include <chrono>
#include <thread>


namespace view::player
{

ui::Color getGaugeColor(float time)
{
    if (time > 0.5f)
    {
        return ui::Color::Green;
    }
    else if (time > 0.25f)
    {
        return ui::Color::Yellow;
    }
    else
    {
        return ui::Color::Red;
    }
}

void countDownThread(ui::ScreenInteractive& screen)
{
    for (;;)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        screen.PostEvent(ui::Event::Custom);
    }
}

void Loop(ui::ScreenInteractive& screen)
{
    std::string word;
    ui::Component inputWord = ui::Input(&word, L"Enter a word");

    auto component = ui::Container::Vertical({ inputWord });

    uint32_t level = 0;
    float time = 1.0f;


    auto renderer = ui::Renderer(component, [&] {
        auto document = ui::vbox({
            ui::hbox({
                ui::text("Level: " + std::to_string(level)) | size(ui::WIDTH, ui::EQUAL, 15),
                ui::separator(),
                ui::text("Score: 0") | size(ui::WIDTH, ui::EQUAL, 15),
                ui::separator(),
                ui::text("Pass: 0") | size(ui::WIDTH, ui::EQUAL, 15),
            }),
            ui::separator(),
            ui::gauge(time) | ui::color(getGaugeColor(time)),
            ui::separator(),
            ui::text("Word: " + word),

            inputWord->Render(),
            });

        document = document | ui::border | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
        return document;
        });

    renderer |= ui::CatchEvent([&](ui::Event event) {
        if (event == ui::Event::Custom)
        {
            if (time > 0.0f)
            {
                time -= 0.01f;
            }
            else
            {
                time = 1.0f;
                level++;
            }
        }
        return false;
        });

    std::thread t(countDownThread, std::ref(screen));
    t.detach();

    screen.Loop(renderer);

}


} // namespace view::player