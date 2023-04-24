#include "view/rank.hpp"



namespace view::rank
{

void records2rows(const std::vector<Player>& players, std::vector<std::string>& rows)
{
    rows.clear();
    for (auto& player : players)
    {
        char row[128];
        std::snprintf(row, sizeof(row), "%5.1d | %16.16s | %7.1d | %7.1d | %6.1d |",
            player.GetId(), player.GetName().c_str(), player.GetScore(), player.GetLevel(), player.GetPassNum()
        );
        rows.push_back(row);
    }
}


void Loop(ui::ScreenInteractive& screen)
{

    std::vector<Player> players;
    std::vector<std::string> rows;
    std::pair<int, bool> sort = { 0, true }; // { column, asc }
    int selected = 0;

    db::FetchPlayers(players);
    records2rows(players, rows);

    auto tbody = ui::Menu(&rows, &selected);

    auto container = ui::Container::Horizontal({
            tbody
        });

    container |= ui::CatchEvent([&](ui::Event e) {
        const std::vector<ui::Event> keymap = {
            ui::Event::Character('i'),
            ui::Event::Character('n'),
            ui::Event::Character('s'),
            ui::Event::Character('l'),
            ui::Event::Character('p'),
        };
        for (size_t i = 0;i < keymap.size();i++)
        {
            if (e != keymap[i])
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
            db::FetchPlayers(players, sort.first, sort.second);
            records2rows(players, rows);

            return true;
        }
        return false;

        });

    auto renderer = ui::Renderer(container, [&] {

        ui::Elements theadCols({});
        for (int i = 0; i < 5; i++)
        {
            const std::vector <std::pair<std::string, int> > cols = {
                {"ID", 5 + 3},
                {"Name", 16 + 2},
                {"Score", 7 + 2},
                {"Level", 7 + 2},
                {"Pass", 6 + 2}
            };
            std::string arrow = "";
            if (i == sort.first)
            {
                arrow = sort.second ? " ▲" : " ▼";
            }
            theadCols.push_back(ui::text(cols[i].first + arrow) | ui::center | ui::size(ui::WIDTH, ui::EQUAL, cols[i].second));
            theadCols.push_back(ui::separator());
        }

        auto table = ui::vbox({
            ui::hbox(theadCols),
            ui::separator(),
            tbody->Render() | ui::vscroll_indicator | ui::frame | ui::size(ui::HEIGHT, ui::LESS_THAN, 10)
            });

        auto document = ui::vbox({
            ui::text(L"排行榜") | ui::center | ui::bold,

            ui::separator(),

            table | ui::border,

            });


        document = document | ui::border | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
        return document;
        });


    screen.Loop(renderer);
}

} // namespace view::rank
