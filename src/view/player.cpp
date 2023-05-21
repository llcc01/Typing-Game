#include "view/player.hpp"
#include <iostream>
#include <chrono>
#include <thread>



#include "view/char.hpp"
#include "utils/string.h"
#include "db.hpp"


namespace view::player
{

inline ui::Color getGaugeColor(float time)
{
    if (time > 0.4f)
    {
        return ui::Color::Green;
    }
    else if (time > 0.1f)
    {
        return ui::Color::Yellow;
    }
    else
    {
        return ui::Color::Red;
    }
}

bool timerRunning = false;

void timerThread(ui::ScreenInteractive& screen, bool& countdownRunning, int16_t& countdown)
{
    while(timerRunning)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (countdownRunning)
        {
            countdown--;
            if (countdown <= 0)
            {
                countdownRunning = false;
            }
            screen.PostEvent(ui::Event::Custom);
        }
    }
}

void Loop(ui::ScreenInteractive& screen, Player& player)
{
    std::string wordInput;
    std::string word = "Test";
    std::vector<std::string> wordList;



    auto uiInputWord = ui::Input(&wordInput, L"Enter a word");
    auto uiCanvas = CharCanvas(12 * 16, 32);

    auto component = ui::Container::Vertical({ uiInputWord });

    float timePercent = 1.0f;
    uint16_t time = 100;
    int16_t countdown = time;
    bool countdownRunning = false;

    auto setNextWord = [&] {
        countdown = time;
        wordInput = "";
        size_t num = db::GetRandomWords(wordList, player.GetLevel(), 1);
        if (num == 0)
        {
            word = "NoWord";
        }
        else
        {
            word = wordList[0];
        }
        uiCanvas.Clear();
        uiCanvas.DrawString(0, 0, word, ui::Color::Red);
        countdownRunning = true;
    };

    setNextWord();


    auto renderer = ui::Renderer(component, [&] {
        auto document = ui::vbox({
            ui::hbox({
                ui::text(L"等级: " + std::to_wstring(player.GetLevel())) | size(ui::WIDTH, ui::EQUAL, 15),
                ui::separator(),
                ui::text(L"经验: " + std::to_wstring(player.GetScore())) | size(ui::WIDTH, ui::EQUAL, 15),
                ui::separator(),
                ui::text(L"通关: " + std::to_wstring(player.GetPassNum())) | size(ui::WIDTH, ui::EQUAL, 15),
                ui::separator(),
                ui::text(L"姓名: " + utils::to_wide_string(player.GetName())) | size(ui::WIDTH, ui::EQUAL, 24),
                ui::separator(),
            }),

            ui::separator(),

            ui::gauge(timePercent) | ui::color(getGaugeColor(timePercent)),

            ui::separator(),

            ui::text("单词: "),
            ui::canvas(uiCanvas),

            ui::separator(),


            uiInputWord->Render(),
            });

        if (countdownRunning)
        {
            wordInput = "";
        }
        else if (wordInput == word)
        {
            player.SetPassNum(player.GetPassNum() + 1);
            player.SetScore(player.GetScore() + 1);
            player.SetLevel(player.GetLevel() + 1);
            setNextWord();
        }

        document = document | ui::border;
        return document;
        });

    renderer |= ui::CatchEvent([&](ui::Event event) {
        if (event == ui::Event::Custom)
        {
            if (countdown == 0)
            {
                uiCanvas.Clear();
            }
            timePercent = (float)countdown / time;
        }
        return false;
        });

    timerRunning = true;
    std::thread t(timerThread, std::ref(screen), std::ref(countdownRunning), std::ref(countdown));
    t.detach();

    screen.Loop(renderer);
    timerRunning = false;

}


} // namespace view::player