#include <pigaco/WebNavigationBar.hpp>

#include <Wt/WStackedWidget>
#include <Wt/WMenu>
#include <Wt/WText>

#include <easylogging++.h>

namespace pigaco
{

WebNavigationBar::WebNavigationBar(Wt::WContainerWidget *parent)
{
    m_navbar = new Wt::WNavigationBar(this);
    m_navbar->setTitle("PiGaCo-Web");
    m_navbar->setResponsive(true);
}
WebNavigationBar::~WebNavigationBar()
{

}
void WebNavigationBar::addMainMenuItem(const std::string &title, Wt::WWidget *item, const std::string &link)
{
    if(m_mainMenu == nullptr)
    {
        LOG(FATAL) << "You have to set a destination for the menu first!";
        return;
    }
    if(link != "")
    {
        m_mainMenu->addItem(title, item)
            ->setLink(Wt::WLink(Wt::WLink::InternalPath, link));
    }
    else
    {
        m_mainMenu->addItem(title, item);
    }
}
void WebNavigationBar::setDest(Wt::WStackedWidget *dest)
{
    if(m_mainMenu != nullptr)
        delete m_mainMenu;

    //Main Menu (from the left)
    m_mainMenu = new Wt::WMenu(dest, this);
    m_navbar->addMenu(m_mainMenu);
}

}
