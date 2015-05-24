#pragma once

#include <memory>
#include <Wt/WContainerWidget>

#include <piga/PlayerManager.hpp>

namespace pigaco
{
class App;

class WebPlayers : public Wt::WContainerWidget
{
    public:
        WebPlayers(App *app, Wt::WContainerWidget *parent = 0);
        virtual ~WebPlayers();

    private:
        App *m_app;

        std::shared_ptr<piga::PlayerManager> m_playerManager;
};
}
