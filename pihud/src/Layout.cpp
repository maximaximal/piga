#include <pihud/Layout.hpp>

#include <algorithm>

namespace PiH
{
    Layout::Layout(Widget *parent)
        : Widget(parent)
    {

    }
    Layout::~Layout()
    {
        //Unset the widgets.
        if(m_layouter != nullptr)
        {
            m_layouter->m_widgets = nullptr;
            delete m_layouter;
            m_layouter = nullptr;
        }
    }
    void Layout::setLayouter(Layouter *layouter)
    {
        if(m_layouter != nullptr)
            delete m_layouter;
        m_layouter = layouter;
        //Set the widgets to the layouter.
        m_layouter->m_widgets = &m_widgets;
    }
    void Layout::updateLayout()
    {
        if(m_layouter != nullptr)
        {
            m_layouter->setBoundingBox(getBoundingBox());
            m_layouter->setBoxes(m_widgets);
        }
    }
    void Layout::addWidget(std::shared_ptr<Widget> widget)
    {
        m_widgets.push_back(widget);
    }
    void Layout::removeWidget(std::shared_ptr<Widget> widget)
    {
        auto it = std::find(m_widgets.begin(), m_widgets.end(), widget);
        m_widgets.erase(it);
    }
    bool Layout::memberInFocus()
    {
        for(auto &widget : m_widgets)
        {
            //Check if the member can be casted into a layout
            std::shared_ptr<Layout> layout;
            if((layout = std::dynamic_pointer_cast<Layout>(widget)))
            {
                if(layout->memberInFocus())
                    return true;
            }
            else
            {
                if(widget->isFocused())
                    return true;
            }
        }
        return false;
    }
    void Layout::onEvent(const Event &e)
    {
        if(m_layouter != nullptr)
            m_layouter->onEvent(e);
    }
    void Layout::onUpdate(float frametime)
    {
        if(m_layouter != nullptr)
            m_layouter->onUpdate(frametime);
    }
    void Layout::onRender(SDL_Renderer *renderer, const FloatRect &offset)
    {
        if(m_layouter != nullptr)
            m_layouter->onRender(renderer, offset);
    }
    void Layout::updateBoundingBox()
    {
        updateLayout();
    }
}
