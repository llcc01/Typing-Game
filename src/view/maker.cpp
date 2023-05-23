#include "view/maker.hpp"
// #include "db.hpp"
#include "rpc/client.hpp"

namespace view::maker
{

using namespace rpc::client;

void records2rows(const std::vector<Word>& words, std::vector<std::string>& rows)
{
    rows.clear();
    for (auto& word : words)
    {
        char row[128];
        std::snprintf(row, sizeof(row), "%5.1d │ %16.16s │ %6.1d │ %6.1d │",
            word.GetId(), word.GetWord().c_str(), word.GetLevel(), word.GetMakerId()
        );
        rows.push_back(row);
    }
}

void Loop(ui::ScreenInteractive& screen, Maker& maker)
{
    std::string word = "";
    std::string level = "";
    std::string msg = "";
    std::vector<std::string> rows;
    std::vector<Word> words;
    int rowSelected = 0;

    auto fetchData = [&]() {
        db::FetchWords(words);
        records2rows(words, rows);

    };

    fetchData();

    auto tbody = ui::Menu(&rows, &rowSelected);

    tbody |= ui::CatchEvent([&](ui::Event e) {
        if (e == ui::Event::Delete)
        {
            if (rowSelected >= 0 && rowSelected < words.size())
            {
                db::DeleteWord(words[rowSelected].GetId());
                fetchData();
            }
            return true;
        }
        return false;
        });

    ui::InputOption wordOption;
    wordOption.on_enter = [&] {
        screen.PostEvent(ui::Event::Tab);
    };
    auto uiInputWord = ui::Input(&word, L"请输入", wordOption);

    ui::InputOption levelOption;
    levelOption.on_enter = [&] {
        screen.PostEvent(ui::Event::Tab);
    };
    auto uiInputLevel = ui::Input(&level, "请输入", levelOption);

    auto buttonAdd = ui::Button(L"添加", [&] {
        if (word == "" || level == "")
        {
            msg = "单词和等级不能为空";
            return;
        }

        try
        {
            uint32_t levelNum = std::stoi(level);
            if (levelNum <= 0)
            {
                msg = "等级必须大于0";
                return;
            }
            db::AddWord(word, levelNum, maker.GetId());
        }
        catch (const std::exception& e)
        {
            if (e.what() == std::string("stoi"))
            {
                msg = "等级必须为数字";
            }
            else
            {
                msg = e.what();
            }
            return;
        }


        msg = "添加成功";
        fetchData();
        word = "";
        level = "";
        maker.SetQuesNum(maker.GetQuesNum() + 1);
        maker.SetLevel(maker.GetQuesNum() / 10);

        }, ui::ButtonOption::Animated(ui::Color::LightSkyBlue1));
    auto buttonReturn = ui::Button(L"返回", [&] {
        screen.ExitLoopClosure()();

        }, ui::ButtonOption::Animated(ui::Color::LightSeaGreen));

    auto component = ui::Container::Vertical({ tbody, uiInputWord, uiInputLevel, buttonAdd, buttonReturn });


    auto renderer = ui::Renderer(component, [&] {
        auto document = ui::vbox({
            ui::text(L"出题") | ui::center | ui::bold,

            ui::separator(),

            ui::hbox({

            ui::vbox({
                ui::text(L"    ID  │       单词       │  等级  │  出题  │") | ui::bold,
                ui::separator(),
                tbody->Render() | ui::vscroll_indicator | ui::frame | ui::size(ui::HEIGHT, ui::LESS_THAN, 10)
            }) | ui::border,

            ui::separator(),

            ui::vbox({
                ui::hbox({
                    ui::text(L"单词") | size(ui::WIDTH, ui::EQUAL, 4),
                    ui::separator(),
                    uiInputWord->Render() ,
                }) | ui::border,


                ui::hbox({
                    ui::text(L"等级") | size(ui::WIDTH, ui::EQUAL, 4),
                    ui::separator(),
                    uiInputLevel->Render() ,
                }) | ui::border,

                ui::hbox({
                    buttonAdd->Render() | ui::center,
                    buttonReturn->Render() | ui::center,
                }) | ui::center,

                ui::text(msg) | ui::center | ui::color(ui::Color::Red),

                }) | ui::size(ui::WIDTH, ui::EQUAL, 30)
            })



            });


        document = document | ui::border;
        return document;
        });


    screen.Loop(renderer);
}

} // namespace view::login
