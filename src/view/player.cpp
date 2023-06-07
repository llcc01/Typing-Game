#include "view/player.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>


#include "view/char.hpp"
#include "utils/string.h"
// #include "db.hpp"
#include "rpc/client.hpp"
#include "rpc/p2p.hpp"


#define COUNTDOWN_MAX 100
#define ONLINE_COUNTDOWN_MAX 100

namespace view::player
{

using namespace rpc::client;

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
std::atomic<int32_t> peerOnlineCountdown(0);

void timerThread(ui::ScreenInteractive& screen, bool& countdownRunning, int16_t& countdown, bool& countRunning, int16_t& count)
{
    while (timerRunning)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (countdownRunning)
        {
            countdown--;
            if (countdown <= 0)
            {
                countdownRunning = false;
                countRunning = true;
            }
        }
        if (countRunning)
        {
            count++;
        }
        if (peerOnlineCountdown > 0)
        {
            peerOnlineCountdown--;
        }
        screen.PostEvent(ui::Event::Custom);
    }
}

void Loop(ui::ScreenInteractive& screen, Player& player, uint64_t peerId)
{
    rpc::P2P p2p(0);
    Player peer;

    std::string wordInput;
    std::string word = "Test";
    std::vector<std::string> wordList;

    auto uiInputWord = ui::Input(&wordInput, L"Enter a word");
    auto uiCanvas = CharCanvas(12 * 16, 32);

    auto component = ui::Container::Vertical({ uiInputWord });

    float timePercent = 1.0f;
    int16_t time = COUNTDOWN_MAX;
    int16_t countdown = time;
    bool countdownRunning = false;
    int16_t count = 0;
    bool countRunning = false;

    auto setNextWord = [&](std::string newWord = "") {
        time = COUNTDOWN_MAX;
        if (peerId == 0)
        {
            time -= player.GetPassNum() * 10;
        }
        if (time < 10)
        {
            time = 10;
        }
        countdown = time;
        wordInput = "";
        if (newWord == "")
        {
            size_t num = db::GetRandomWords(wordList, player.GetPassNum(), 1);
            if (num == 0)
            {
                word = "NoWord";
            }
            else
            {
                word = wordList[0];
            }
        }
        else
        {
            word = newWord;
        }
        uiCanvas.Clear();
        uiCanvas.DrawString(0, 0, word, ui::Color::Red);
        countdownRunning = true;
        countRunning = false;
        count = 0;
    };

    auto selfPass = [&] {
        db::GetUser(player, player.GetId());
        player.SetPassNum(player.GetPassNum() + 1);
        player.SetScore(player.GetScore() + player.GetPassNum() * 300 / count);
        player.SetLevel(player.GetScore() / 100);
        db::UpdateUser(player);
        setNextWord();
        p2p.Send(peer.GetIp(), peer.GetRxPort(), "pass?nextword=" + word, UserRole::Player, player.GetId());
    };

    auto peerPass = [&] {
        auto req = p2p.GetRequest();
        std::string nextWord = req->GetParam("nextword");
        setNextWord(nextWord);
    };

    if (peerId == 0)
    {
        setNextWord();
    }
    else
    {
        db::GetUser(peer, peerId);
        int64_t res = p2p.Setup();
        if (res < 0)
        {
            std::cerr << "p2p.Setup() failed" << std::endl;
            return;
        }
        player.SetRxPort(res);
        db::UpdateUser(player);
        p2p.Start();
        res = p2p.Send(peer.GetIp(), peer.GetRxPort(), "ping", UserRole::Player, player.GetId());
        if (res < 0)
        {
            std::cerr << "p2p.Send() failed" << std::endl;
            return;
        }
    }

    auto getMsg = [&] {
        if (peerId == 0)
        {
            return "";
        }

        if (peerOnlineCountdown == 0)
        {
            return "等待对手";
        }

        return countdownRunning ? "对手在线" : "对手在线, 按回车开始";
    };

    auto renderer = ui::Renderer(component, [&] {
        std::string msg = getMsg();
        if (peerId != 0)
        {
            if (p2p.GetRxFlag())
            {
                auto req = p2p.GetRequest();
                if (req->GetUserId() == peerId)
                {
                    if (peerOnlineCountdown == 0)
                    {
                        db::GetUser(peer, peerId);
                    }
                    peerOnlineCountdown = ONLINE_COUNTDOWN_MAX;
                    if (req->GetAction() == "ping")
                    {
                        p2p.Send(peer.GetIp(), peer.GetRxPort(), "pong", UserRole::Player, player.GetId());
                    }
                    else if (req->GetAction() == "pass")
                    {
                        msg = "对手已通关";
                        peerPass();
                    }
                    else if (req->GetAction() == "start")
                    {
                        msg = "对手开始游戏";
                        word = req->GetParam("word");
                        setNextWord(word);
                        countdownRunning = true;
                    }
                }
                p2p.SetRxFlag(false);
            }
            if (peerOnlineCountdown < ONLINE_COUNTDOWN_MAX / 2)
            {
                p2p.Send(peer.GetIp(), peer.GetRxPort(), "ping", UserRole::Player, player.GetId());
            }
        }

        char countDownStr[10];
        snprintf(countDownStr, sizeof(countDownStr), "%.1fs", countdown / 10.0);

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
                ui::text(L"用时: " + std::to_wstring(count / 10) + L"s") | size(ui::WIDTH, ui::EQUAL, 15),
                ui::separator(),
                ui::text(L"对手ID: " + std::to_wstring(peerId)) | size(ui::WIDTH, ui::EQUAL, 15),
            }),

            ui::separator(),

            ui::text(L"信息：" + utils::to_wide_string(msg)),

            ui::separator(),

            ui::hbox({
                ui::text(countDownStr),
                ui::separator(),
                ui::gauge(timePercent) | ui::color(getGaugeColor(timePercent)),
            }),

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
            selfPass();
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
        else if (event == ui::Event::Return)
        {
            if (!countdownRunning)
            {
                setNextWord();
                p2p.Send(peer.GetIp(), peer.GetRxPort(), "start?word=" + word, UserRole::Player, player.GetId());
                countdownRunning = true;
            }
        }
        return false;
        });

    timerRunning = true;
    std::thread t(timerThread,
        std::ref(screen),
        std::ref(countdownRunning), std::ref(countdown),
        std::ref(countRunning), std::ref(count));
    t.detach();

    screen.Loop(renderer);
    timerRunning = false;
}


} // namespace view::player