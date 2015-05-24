#pragma once

#include <Wt/WApplication>
#include <Wt/WEnvironment>

#include <Wt/WContainerWidget>
#include <Wt/WHBoxLayout>
#include <Wt/WStackedWidget>

namespace pigaco
{
class App;

class WebNavigationBar;

class WebPlayers;
class WebGames;
class WebInputs;

class WebAdmin : public Wt::WApplication
{
    public:
        WebAdmin(const Wt::WEnvironment &env, pigaco::App *app);
        virtual ~WebAdmin();

    private:
        void internalPathChangedHandler(const std::string &path);

        Wt::WContainerWidget *m_root = nullptr;
        Wt::WStackedWidget *m_pages = nullptr;

        App *m_app;

        //Navigation
        WebNavigationBar *m_navBar = nullptr;

        //Pages
        WebPlayers *m_page_players = nullptr;
        WebGames *m_page_games = nullptr;
        WebInputs *m_page_inputs = nullptr;
};
}
