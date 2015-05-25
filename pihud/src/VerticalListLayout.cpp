#include <pihud/VerticalListLayout.hpp>
#include <pihud/Config.hpp>
#include <pihud/pihud.hpp>

namespace PiH
{
    VerticalListLayout::VerticalListLayout()
    {

    }
    VerticalListLayout::~VerticalListLayout()
    {

    }
    void VerticalListLayout::setBoxes(Layouter::LayoutedWidgets &widgets)
    {
        float x = getBoundingBox().x, y = getBoundingBox().y;
        for(std::shared_ptr<PiH::Widget> &widget : widgets)
        {
            if(m_centered)
            {
                x = getBoundingBox().x + getBoundingBox().w / 2 - widget->getBoundingBox().w / 2;
            }
            widget->setBoundingBox(x, y, widget->getBoundingBox().w, widget->getBoundingBox().h);
            y += widget->getBoundingBox().h + getSpacing();
        }
    }
    void VerticalListLayout::setSpacing(int spacing)
    {
        m_spacing = spacing;
    }
    void VerticalListLayout::onEvent(const Event &e)
    {
        Layouter::onEvent(e);
        if(e.type == EventType::Focus)
        {
            if(!e.focus.wasHandled() && (memberInFocus() || isFocused()))
            {
                if(e.focus.direction == UP)
                {
                    if(m_currentlyFocused != 0)
                    {
                        m_currentlyFocused -= 1;
                        e.focus.setHandled();
                        getGlobalConfig()->getFocusManager()->setFocused(getCurrentlyFocusedWidget(), e.playerID);
                    }
                }
                else if(e.focus.direction == DOWN)
                {
                    if((m_currentlyFocused + 1) < m_widgets->size())
                    {
                        m_currentlyFocused += 1;
                        e.focus.setHandled();
                        getGlobalConfig()->getFocusManager()->setFocused(getCurrentlyFocusedWidget(), e.playerID);
                    }
                }
            }
        }
    }
    int VerticalListLayout::getSpacing()
    {
        return m_spacing;
    }
    bool VerticalListLayout::getCentered()
    {
        return m_centered;
    }
    void VerticalListLayout::setCentered(bool centered)
    {
        m_centered = centered;
    }
    std::shared_ptr<Widget> VerticalListLayout::getCurrentlyFocusedWidget()
    {
        return (*m_widgets)[m_currentlyFocused];
    }
    void VerticalListLayout::updateBoundingBox()
    {

    }
}


