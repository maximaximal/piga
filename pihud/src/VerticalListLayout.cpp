#include <pihud/VerticalListLayout.hpp>
#include <pihud/Config.hpp>
#include <pihud/pihud.hpp>

namespace PiH
{
    void VerticalListLayout::setBoxes(Layouter::LayoutedWidgets &widgets)
    {
        float x = 0;
        for(std::shared_ptr<PiH::Widget> &widget : widgets)
        {
            widget->setBoundingBox(x, getBoundingBox().y, widget->getBoundingBox().w, getBoundingBox().h);
            x += widget->getBoundingBox().w + getSpacing();
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
                if(e.focus.direction == LEFT)
                {
                    if(m_currentlyFocused - 1 >= 0 && m_currentlyFocused != 0)
                    {
                        m_currentlyFocused -= 1;
                        e.focus.setHandled();
                        getGlobalConfig()->getFocusManager()->setFocused(getCurrentlyFocusedWidget(), e.playerID);
                    }
                }
                else if(e.focus.direction == RIGHT)
                {
                    if(m_currentlyFocused + 1 < m_widgets->size())
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
    std::shared_ptr<Widget> VerticalListLayout::getCurrentlyFocusedWidget()
    {
        return (*m_widgets)[m_currentlyFocused];
    }
    void VerticalListLayout::updateBoundingBox()
    {

    }
}

