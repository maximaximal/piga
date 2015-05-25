#include <pigaco/App.hpp>
#include <pigaco/DirectoryScanner.hpp>
#include <QList>
#include <Wt/WTable>
#include <Wt/WText>

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
        Game *game = m_dirScanner->getGames()[i].get();

        gamesTable->elementAt(i + 1, 0)->addWidget(new Wt::WText(game->getConfig(piga::GameHost::Name)));
        gamesTable->elementAt(i + 1, 1)->addWidget(new Wt::WText(game->getConfig(piga::GameHost::Description)));
        gamesTable->elementAt(i + 1, 2)->addWidget(new Wt::WText(game->getConfig(piga::GameHost::Author)));
        gamesTable->elementAt(i + 1, 3)->addWidget(new Wt::WText(game->getConfig(piga::GameHost::Version)));
    }
}
WebGames::~WebGames()
{

}

}
