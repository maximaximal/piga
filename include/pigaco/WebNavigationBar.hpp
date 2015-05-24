#pragma once

#include <Wt/WContainerWidget>
#include <Wt/WNavigationBar>

#include <Wt/WMenu>

namespace pigaco
{
class WebNavigationBar : public Wt::WContainerWidget
{
    public:
        WebNavigationBar(Wt::WContainerWidget *parent = 0);
        virtual ~WebNavigationBar();

        void addMainMenuItem(const std::string &title, Wt::WWidget *item, const std::string &link = "");
        void setDest(Wt::WStackedWidget *dest);
    private:
        Wt::WNavigationBar *m_navbar = nullptr;
        Wt::WMenu *m_mainMenu = nullptr;

};
}
