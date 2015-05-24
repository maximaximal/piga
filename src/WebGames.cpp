#include <pigaco/App.hpp>
#include <pigaco/DirectoryScanner.hpp>
#include <QList>

#include <pigaco/WebGames.hpp>

namespace pigaco
{

WebGames::WebGames(App *app, Wt::WContainerWidget *parent)
    : Wt::WContainerWidget(parent), m_app(app)
{
    m_dirScanner = app->getDirectoryScanner();

    Wt::WTable *gamesTable = new Wt::WTable(this);
    gamesTable->setHeaderCount(1);

    gamesTable->elementAt(0, 0)->addWidget(new Wt::WText("Name"));
    gamesTable->elementAt(0, 1)->addWidget(new Wt::WText("Description"));
    gamesTable->elementAt(0, 2)->addWidget(new Wt::WText("Author"));
    gamesTable->elementAt(0, 3)->addWidget(new Wt::WText("Version"));

    for(int i = 0; i < m_dirScanner->getGames().count(); ++i)
    {
        piga::Player *player = m_playerManager->getPlayer(i);

        playersTable->elementAt(i + 1, 0)->addWidget(new Wt::WText(std::to_string(player->getPlayerID())));
        playersTable->elementAt(i + 1, 1)->addWidget(new Wt::WText(player->getName()));
    }
}
WebGames::~WebGames()
{

}

}
