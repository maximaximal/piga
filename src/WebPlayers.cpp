//App has to be included before Wt because of sigc / Qt / Wt signal incompatabilities.
#include <pigaco/App.hpp>

#include <pigaco/WebPlayers.hpp>
#include <Wt/WTable>
#include <Wt/WText>

namespace pigaco
{

WebPlayers::WebPlayers(App *app, Wt::WContainerWidget *parent)
    : Wt::WContainerWidget(parent), m_app(app)
{
    m_playerManager = m_app->getPlayerManager();

    Wt::WTable *playersTable = new Wt::WTable(this);
    playersTable->setHeaderCount(1);

    playersTable->elementAt(0, 0)->addWidget(new Wt::WText("ID"));
    playersTable->elementAt(0, 1)->addWidget(new Wt::WText("Username"));

    for(int i = 0; i < m_playerManager->size(); ++i)
    {
        piga::Player *player = m_playerManager->getPlayer(i);

        playersTable->elementAt(i + 1, 0)->addWidget(new Wt::WText(std::to_string(player->getPlayerID())));
        playersTable->elementAt(i + 1, 1)->addWidget(new Wt::WText(player->getName()));
    }

}
WebPlayers::~WebPlayers()
{

}

}
