#pragma once

#include <Wt/WContainerWidget>

namespace pigaco
{
class App;

class WebInputs : public Wt::WContainerWidget
{
    public:
        WebInputs(App *app, Wt::WContainerWidget *parent = 0);
        virtual ~WebInputs();

    private:
        App *m_app;

        bool m_bUp = false;
        bool m_bDown = false;
        bool m_bLeft = false;
        bool m_bRight = false;
        int m_player = 0;
};
}
