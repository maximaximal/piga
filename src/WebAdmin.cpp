#include <pigaco/WebAdmin.hpp>

#include <Wt/WBootstrapTheme>

#include <pigaco/WebNavigationBar.hpp>
#include <pigaco/WebGames.hpp>
#include <pigaco/WebPlayers.hpp>
#include <pigaco/WebInputs.hpp>

namespace pigaco
{

WebAdmin::WebAdmin(const Wt::WEnvironment &env, App *app)
    : Wt::WApplication(env), m_app(app)
{
    setTheme(new Wt::WBootstrapTheme());

    m_root = new Wt::WContainerWidget();
    this->addGlobalWidget(m_root);


    m_navBar = new WebNavigationBar();
    m_root->addWidget(m_navBar);

    m_pages = new Wt::WStackedWidget();
    m_root->addWidget(m_pages);
    m_navBar->setDest(m_pages);

    m_page_games = new WebGames(app, m_pages);
    m_navBar->addMainMenuItem("Games", m_page_games, "/games");
    m_page_players = new WebPlayers(app, m_pages);
    m_navBar->addMainMenuItem("Players", m_page_players, "/players");
    m_page_inputs = new WebInputs(app, m_pages);
    m_navBar->addMainMenuItem("Inputs", m_page_inputs, "/inputs");

    this->internalPathChanged().connect(this, &WebAdmin::internalPathChangedHandler);
}
WebAdmin::~WebAdmin()
{

}
void WebAdmin::internalPathChangedHandler(const std::string &path)
{

}

}
