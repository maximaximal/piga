#include <pihud/HorizontalListLayout.hpp>
#include <pihud/Config.hpp>
#include <pihud/pihud.hpp>

namespace PiH
{
    HorizontalListLayout::HorizontalListLayout()
    {

    }
    HorizontalListLayout::~HorizontalListLayout()
    {

    }
    void HorizontalListLayout::setBoxes(Layouter::LayoutedWidgets &widgets)
    {
        float x = 0;
        for(std::shared_ptr<PiH::Widget> &widget : widgets)
        {
            widget->setBoundingBox(x, getBoundingBox().y, widget->getBoundingBox().w, getBoundingBox().h);
            x += widget->getBoundingBox().w + getSpacing();
        }
    }
    void HorizontalListLayout::setSpacing(int spacing)
    {
        m_spacing = spacing;
    }
    void HorizontalListLayout::onEvent(const Event &e)
    {
        Layouter::onEvent(e);
        if(e.type == EventType::Focus)
        {
            if(!e.focus.wasHandled() && (memberInFocus() || isFocused()))
            {
                if(e.focus.direction == LEFT)
                {
                    if(m_currentlyFocused != 0)
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
    int HorizontalListLayout::getSpacing()
    {
        return m_spacing;
    }
    std::shared_ptr<Widget> HorizontalListLayout::getCurrentlyFocusedWidget()
    {
        return (*m_widgets)[m_currentlyFocused];
    }
    void HorizontalListLayout::updateBoundingBox()
    {

    }
}

