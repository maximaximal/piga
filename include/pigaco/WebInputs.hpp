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
};
}
