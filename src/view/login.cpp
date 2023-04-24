#include "view/login.hpp"
#include "db.hpp"

namespace view::login
{

void Loop(ui::ScreenInteractive& screen)
{
    std::string name;
    std::string password;
    uint64_t id = 0;
    std::string msg = "";

    ui::InputOption nameOption;
    nameOption.on_enter = [&] {
        screen.PostEvent(ui::Event::Tab);
    };
    auto uiInputName = ui::Input(&name, L"请输入", nameOption);

    ui::InputOption passwordOption;
    passwordOption.password = true;
    passwordOption.on_enter = [&] {
        screen.PostEvent(ui::Event::Tab);
    };
    auto uiInputPassword = ui::Input(&password, "请输入", passwordOption);

    int role = 0;
    std::vector<std::wstring> roleList = { L"玩家", L"管理员" };
    auto uiRadioRole = ui::Radiobox(&roleList, &role);

    auto buttonLogin = ui::Button(L"登录", [&] {
        if (name == "" || password == "")
        {
            msg = "用户名或密码不能为空";
            return;
        }
        
        id = Database::GetInstance().CheckUser(name, password, UserType(role));
        if (id == 0)
        {
            msg = "用户名或密码错误";
            return;
        }

        msg = "登录成功";
        screen.ExitLoopClosure()();

        }, ui::ButtonOption::Animated(ui::Color::LightSkyBlue1));
    auto buttonSignup = ui::Button(L"注册", [&] {
        if (name == "" || password == "")
        {
            msg = "用户名或密码不能为空";
            return;
        }

        id = Database::GetInstance().AddUser(name, password, UserType(role));
        if (id == 0)
        {
            msg = "用户名已存在";
            return;
        }

        msg = "注册成功";

        }, ui::ButtonOption::Animated(ui::Color::LightSeaGreen));

    auto component = ui::Container::Vertical({ uiInputName, uiInputPassword, uiRadioRole, buttonLogin, buttonSignup});


    auto renderer = ui::Renderer(component, [&] {
        auto document = ui::vbox({
            ui::text(L"单词消除游戏") | ui::center | ui::bold,

            ui::separator(),

            ui::hbox({
                ui::text(L"用户") | size(ui::WIDTH, ui::EQUAL, 4),
                ui::separator(),
                uiInputName->Render() ,
            }) | ui::border,


            ui::hbox({
                ui::text(L"密码") | size(ui::WIDTH, ui::EQUAL, 4),
                ui::separator(),
                uiInputPassword->Render() ,
            }) | ui::border,

            ui::hbox({
                ui::text(L"角色") | size(ui::WIDTH, ui::EQUAL, 4),
                ui::separator(),
                uiRadioRole->Render() ,
            }) | ui::border,

            ui::hbox({
                buttonLogin->Render() | ui::center,
                buttonSignup->Render() | ui::center,
            }) | ui::center,

            ui::text(msg) | ui::center | ui::color(ui::Color::Red),

            });


        document = document | ui::border | ftxui::size(ftxui::WIDTH, ftxui::LESS_THAN, 80);
        return document;
        });


    screen.Loop(renderer);
}

} // namespace view::login
