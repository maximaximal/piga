#include <pihud/Layouter.hpp>
#include <pihud/Layout.hpp>

namespace PiH
{
    Layouter::Layouter(Widget *parent)
    	: Widget(parent)
    {
        //Nothing to do
    }
    Layouter::Layouter(const Layouter &layouter, Widget *parent)
    	: Widget(parent)
    {
        //Nothing to do
    }
    Layouter::~Layouter()
    {
        //Nothing to do
    }
    bool Layouter::memberInFocus()
    {
        if(m_widgets != nullptr)
        {
            for(auto &widget : (*m_widgets))
            {
                //Check if the member can be casted into a layout
                std::shared_ptr<Layout> layout;
                if(layout = std::dynamic_pointer_cast<Layout>(widget))
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
        }
        return false;
    }
    void Layouter::onUpdate(float frametime)
    {
        if(m_widgets != nullptr)
        {
			for(auto &widget : *m_widgets)
			{
				widget->onUpdate(frametime);
			}
        }
    }
    void Layouter::onEvent(const Event &e)
    {
        if(m_widgets != nullptr)
        {
			for(auto &widget : *m_widgets)
			{
				widget->onEvent(e);
			}
        }
    }
    void Layouter::onRender(SDL_Renderer *renderer, const FloatRect &offset)
    {
        if(m_widgets != nullptr)
        {
			for(auto &widget : *m_widgets)
			{
				widget->onRender(renderer, offset);
			}
        }
    }
    void Layouter::setBoxes(LayoutedWidgets &widgets)
    {
        //Default layout: All child-widgets have the same bounding box like the layouter.
        for(auto &widget : widgets)
        {
            widget->setBoundingBox(getBoundingBox());
        }
    }
}
