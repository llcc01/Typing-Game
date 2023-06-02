#include "utils/string.h"

#include "view/rank.hpp"
// #include "db.hpp"
#include "rpc/client.hpp"

namespace view::rank
{

using namespace rpc::client;

void records2rows(const std::vector<Player>& players, std::vector<std::string>& rows)
{
    rows.clear();
    for (auto& player : players)
    {
        char row[128];

        std::snprintf(row, sizeof(row), "%5.1d │ %16.16s │ %7.1d │ %7.1d │ %7.1d │ %s |",
            player.GetId(), player.GetName().c_str(), player.GetScore(), player.GetLevel(), player.GetPassNum(), utils::TimeToString(player.GetLastActiveTime()).c_str()
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
        std::snprintf(row, sizeof(row), "%5.1d │ %16.16s │ %7.1d │ %7.1d │",
            maker.GetId(), maker.GetName().c_str(), maker.GetLevel(), maker.GetQuesNum()
        );
        rows.push_back(row);
    }
}


uint64_t Loop(ui::ScreenInteractive& screen)
{
    uint64_t peerId = 0;

    std::vector<Player> players;
    std::vector<Maker> makers;
    std::vector<std::string> rows;
    std::pair<int, bool> sort = { 0, true }; // { column, asc }
    int rowSelected = 0;
    int tabSelected = 0;
    int lastTabSelected = 0;
    std::string filterId = "";
    std::string filterName = "";
    std::string filter3 = "";
    std::string filter4 = "";
    std::string filter5 = "";

    auto filterIdInput = ui::Input(&filterId, L"筛选");
    auto filterNameInput = ui::Input(&filterName, L"筛选");
    auto filter3Input = ui::Input(&filter3, L"筛选");
    auto filter4Input = ui::Input(&filter4, L"筛选");
    auto filter5Input = ui::Input(&filter5, L"筛选");
    std::vector<std::string> filterStr = { filterId, filterName, filter3, filter4, filter5 };

    auto fetchData = [&]() {

        if (tabSelected == 0)
        {
            db::FetchUsers(players, sort.first, sort.second, filterStr);
            records2rows(players, rows);
        }
        else
        {
            db::FetchUsers(makers, sort.first, sort.second, filterStr);
            records2rows(makers, rows);
        }
    };

    std::vector<std::wstring> tabVals = { L"闯关者", L"出题者" };
    auto tabToggle = ui::Toggle(&tabVals, &tabSelected);

    fetchData();

    auto tbody = ui::Menu(&rows, &rowSelected);

    // container

    auto filterContainer = ui::Container::Horizontal({
        filterIdInput,
        filterNameInput,
        filter3Input,
        filter4Input,
        filter5Input,
        });

    auto container = ui::Container::Horizontal({
        tabToggle,
        filterContainer,
        tbody,
        });

    container |= ui::CatchEvent([&](ui::Event e) {
        if (tbody->Focused())
        {
            const std::vector<std::string> playerKeymap = {
            "i",
            "n",
            "s",
            "l",
            "p",
            "t",
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

            if (e == ui::Event::Return && tabSelected == 0)
            {
                peerId = players[rowSelected].GetId();
                screen.ExitLoopClosure()();
                return true;
            }
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
                {"通关(p)", 7 + 2},
                {"最近在线(t)", 16 + 2}
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

        if (lastTabSelected != tabSelected)
        {
            lastTabSelected = tabSelected;
            rowSelected = 0;
            fetchData();
        }

        bool needFetch = false;
        if (filterId != filterStr[0])
        {
            filterStr[0] = filterId;
            needFetch = true;
        }
        if (filterName != filterStr[1])
        {
            filterStr[1] = filterName;
            needFetch = true;
        }
        if (filter3 != filterStr[2])
        {
            filterStr[2] = filter3;
            needFetch = true;
        }
        if (filter4 != filterStr[3])
        {
            filterStr[3] = filter4;
            needFetch = true;
        }
        if (filter5 != filterStr[4])
        {
            filterStr[4] = filter5;
            needFetch = true;
        }
        if (needFetch)
        {
            fetchData();
        }

        ftxui::Element filter;
        if (tabSelected == 0)
        {
            filter = ui::hbox({
               filterIdInput->Render() | ui::size(ui::WIDTH, ui::EQUAL, playerCols[0].second),
               ui::separator(),
               filterNameInput->Render() | ui::size(ui::WIDTH, ui::EQUAL, playerCols[1].second),
               ui::separator(),
               filter3Input->Render() | ui::size(ui::WIDTH, ui::EQUAL, playerCols[2].second),
               ui::separator(),
               filter4Input->Render() | ui::size(ui::WIDTH, ui::EQUAL, playerCols[3].second),
               ui::separator(),
               filter5Input->Render() | ui::size(ui::WIDTH, ui::EQUAL, playerCols[4].second),
               ui::separator(),
                });


        }
        else
        {
            filter = ui::hbox({
               filterIdInput->Render() | ui::size(ui::WIDTH, ui::EQUAL, makerCols[0].second),
               ui::separator(),
               filterNameInput->Render() | ui::size(ui::WIDTH, ui::EQUAL, makerCols[1].second),
               ui::separator(),
               filter3Input->Render() | ui::size(ui::WIDTH, ui::EQUAL, makerCols[2].second),
               ui::separator(),
               filter4Input->Render() | ui::size(ui::WIDTH, ui::EQUAL, makerCols[3].second),
               ui::separator(),
                });
        }

        auto table = ui::vbox({
                        ui::hbox(theadCols),
                        ui::separator(),
                        filter,
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

    return peerId;
}

} // namespace view::rank
