#include "view/rank.hpp"



namespace view::rank
{

void records2rows(const std::vector<Player>& players, std::vector<std::string>& rows)
{
    rows.clear();
    for (auto& player : players)
    {
        char row[128];
        std::snprintf(row, sizeof(row), "%5.1d | %16.16s | %7.1d | %7.1d | %7.1d |",
            player.GetId(), player.GetName().c_str(), player.GetScore(), player.GetLevel(), player.GetPassNum()
        );
        rows.push_back(row);
    }
}

void records2rows(const std::vector<Maker>& makers, std::vector<std::string>& rows)
{
    rows.clear();
    for (auto& maker : makers)
    {
        char row[128];
        std::snprintf(row, sizeof(row), "%5.1d | %16.16s | %7.1d | %7.1d |",
            maker.GetId(), maker.GetName().c_str(), maker.GetLevel(), maker.GetQuesNum()
        );
        rows.push_back(row);
    }
}


void Loop(ui::ScreenInteractive& screen)
{

    std::vector<Player> players;
    std::vector<Maker> makers;
    std::vector<std::string> rows;
    std::pair<int, bool> sort = { 0, true }; // { column, asc }
    int rowSelected = 0;
    int tabSelected = 0;
    int lastTabSelected = 0;

    auto fetchData = [&]() {
        if (tabSelected == 0)
        {
            db::FetchUsers(players, sort.first, sort.second);
            records2rows(players, rows);
        }
        else
        {
            db::FetchUsers(makers, sort.first, sort.second);
            records2rows(makers, rows);
        }
    };

    std::vector<std::wstring> tabVals = { L"闯关者", L"出题者" };
    auto tabToggle = ui::Toggle(&tabVals, &tabSelected);

    fetchData();

    auto tbody = ui::Menu(&rows, &rowSelected);

    // container
    auto container = ui::Container::Horizontal({
            tabToggle,
            tbody
        });

    container |= ui::CatchEvent([&](ui::Event e) {
        const std::vector<std::string> playerKeymap = {
            "i",
            "n",
            "s",
            "l",
            "p",
        };
        const std::vector<std::string> makerKeymap = {
            "i",
            "n",
            "l",
            "q",
        };
        auto& keymap = (tabSelected == 0) ? playerKeymap : makerKeymap;

        for (size_t i = 0;i < keymap.size();i++)
        {
            if (e.input() != keymap[i])
            {
                continue;
            }
            if (i == sort.first)
            {
                sort.second = !sort.second;
            }
            else
            {
                sort.first = i;
                sort.second = true;
            }

            fetchData();

            return true;
        }
        return false;

        });

    auto renderer = ui::Renderer(container, [&] {

        ui::Elements theadCols({});
        const std::vector <std::pair<std::string, int> > playerCols = {
                {"ID(i)", 5 + 3},
                {"姓名(n)", 16 + 2},
                {"经验(s)", 7 + 2},
                {"等级(l)", 7 + 2},
                {"通关(p)", 7 + 2}
        };
        const std::vector <std::pair<std::string, int> > makerCols = {
                {"ID(i)", 5 + 3},
                {"姓名(n)", 16 + 2},
                {"等级(l)", 7 + 2},
                {"出题(q)", 7 + 2}
        };
        auto& cols = (tabSelected == 0) ? playerCols : makerCols;
        for (int i = 0; i < cols.size(); i++)
        {
            std::string arrow = "";
            if (i == sort.first)
            {
                arrow = sort.second ? " ▲" : " ▼";
            }
            theadCols.push_back(ui::text(cols[i].first + arrow) | ui::center | ui::size(ui::WIDTH, ui::EQUAL, cols[i].second));
            theadCols.push_back(ui::separator());
        }

        if(lastTabSelected != tabSelected)
        {
            lastTabSelected = tabSelected;
            rowSelected = 0;
            fetchData();
        }

        auto table = ui::vbox({
            ui::hbox(theadCols),
            ui::separator(),
            tbody->Render() | ui::vscroll_indicator | ui::frame | ui::size(ui::HEIGHT, ui::LESS_THAN, 10)
            });

        auto document = ui::vbox({
            ui::text(L"排行榜") | ui::center | ui::bold,

            ui::separator(),

            tabToggle->Render(),

            ui::separator(),

            table | ui::border,

            });


        document = document | ui::border | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
        return document;
        });


    screen.Loop(renderer);
}

} // namespace view::rank
