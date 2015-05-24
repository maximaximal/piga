#pragma once

#include <Wt/WContainerWidget>

namespace pigaco
{
class App;

class WebGames : public Wt::WContainerWidget
{
    public:
        WebGames(App *app, Wt::WContainerWidget *parent = 0);
        virtual ~WebGames();

    private:
        App *m_app;
};
}
