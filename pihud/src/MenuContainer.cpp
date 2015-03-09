#include <pihud/MenuContainer.hpp>

namespace PiH
{
	MenuContainer::MenuContainer(Widget *parent)
        : Widget(parent)
    {

    }
    MenuContainer::~MenuContainer()
    {

    }

    void MenuContainer::onEvent(const Event &e)
    {
		if(m_currentPage)
			m_currentPage->onEvent(e);
    }
    void MenuContainer::onUpdate(float frametime)
    {
		if(m_currentPage)
            m_currentPage->onUpdate(frametime);
    }
    void MenuContainer::onRender(SDL_Renderer *renderer, const FloatRect &rect)
    {
		if(m_currentPage)
            m_currentPage->onRender(renderer, rect);
    }

    void MenuContainer::setCurrentPage(const std::string &pageName)
    {
        if(m_pages.count(pageName) > 0)
            m_currentPage = m_pages[pageName];
    }
    void MenuContainer::addPage(std::shared_ptr<HudContainer> page, const std::string &pageName)
    {
        m_pages[pageName] = page;
    }
    void MenuContainer::removePage(const std::string &pageName)
    {
        m_pages.erase(pageName);
    }
    void MenuContainer::updateRectFromBeneath()
    {

    }
    void MenuContainer::updateBoundingBox()
    {
		for(auto &page : m_pages)
        {
            page.second->setBoundingBox(getBoundingBox());
        }
    }
    void MenuContainer::focusGained(int playerID)
    {

    }
    void MenuContainer::focusLost(int playerID)
    {

    }
}
