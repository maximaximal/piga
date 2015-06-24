#include <pigaco/App.hpp>
#include <piga/Events/GameInput.hpp>

#include <pigaco/WebInputs.hpp>
#include <Wt/WPushButton>

#include <Wt/WTable>
#include <Wt/WText>
#include <Wt/WSelectionBox>

#include <easylogging++.h>

#include <pigaco/Players.hpp>

namespace pigaco
{

WebInputs::WebInputs(App *app, Wt::WContainerWidget *parent)
    : Wt::WContainerWidget(parent), m_app(app)
{
    Wt::WText *introText = new Wt::WText("You can inject simple inputs here. \nPlease note that sending inputs over the webform is extremely "
                                         "slow! It is recomended to use a direct client which communicates over the enet UDP networking API.");

    this->addWidget(introText);

    Wt::WSelectionBox *playerSelection = new Wt::WSelectionBox();
    std::shared_ptr<piga::PlayerManager> playerMgr = m_app->getPlayerManager();
    for(int i = 0; i < playerMgr->size(); ++i)
    {
        playerSelection->addItem(Wt::WString(playerMgr->getPlayer(i)->getName()));
    }

    playerSelection->changed().connect(std::bind([=]() {
        m_player = playerSelection->currentIndex();
    }));

    this->addWidget(playerSelection);

    Wt::WTable *table = new Wt::WTable();
    table->setHeaderCount(0);
    table->setWidth(Wt::WLength("50%"));

    Wt::WPushButton *upButton = new Wt::WPushButton("Up");
    Wt::WPushButton *downButton = new Wt::WPushButton("Down");
    Wt::WPushButton *leftButton = new Wt::WPushButton("Left");
    Wt::WPushButton *rightButton = new Wt::WPushButton("Right");

    upButton->clicked().connect(std::bind([&]() {
        m_app->getGameInput()->pushGameEvent(piga::GameEvent(m_player, piga::event::GameInput(piga::GameControl::UP, !m_bUp)));
        m_bUp = !m_bUp;
    }));
    downButton->clicked().connect(std::bind([&]() {
        m_app->getGameInput()->pushGameEvent(piga::GameEvent(m_player, piga::event::GameInput(piga::GameControl::DOWN, !m_bDown)));
        m_bDown = !m_bDown;
    }));
    leftButton->clicked().connect(std::bind([&]() {
        m_app->getGameInput()->pushGameEvent(piga::GameEvent(m_player, piga::event::GameInput(piga::GameControl::LEFT, !m_bLeft)));
        m_bLeft = !m_bLeft;
    }));
    rightButton->clicked().connect(std::bind([&]() {
        m_app->getGameInput()->pushGameEvent(piga::GameEvent(m_player, piga::event::GameInput(piga::GameControl::RIGHT, !m_bRight)));
        m_bRight = !m_bRight;
    }));

    table->elementAt(0, 1)->addWidget(upButton);
    table->elementAt(1, 0)->addWidget(leftButton);
    table->elementAt(1, 2)->addWidget(rightButton);
    table->elementAt(2, 1)->addWidget(downButton);

    this->addWidget(table);
}
WebInputs::~WebInputs()
{

}

}
