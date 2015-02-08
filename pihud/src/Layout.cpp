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
		m_layouter.m_widgets = nullptr;
    }
    void Layout::setLayouter(const Layouter &layouter)
    {
        m_layouter = layouter;
        //Set the widgets to the layouter.
        m_layouter.m_widgets = &m_widgets;
    }
    void Layout::updateLayout()
    {
        m_layouter.setBoundingBox(getBoundingBox());
        m_layouter.setBoxes(m_widgets);
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
    void Layout::onEvent(const Event &e)
    {
	m_layouter.onEvent(e);
    }
    void Layout::onUpdate(float frametime)
    {
	m_layouter.onUpdate(frametime);
    }
    void Layout::onRender(SDL_Renderer *renderer, const FloatRect &offset)
    {
	m_layouter.onRender(renderer, offset);
    }
    void Layout::updateBoundingBox()
    {
	updateLayout();
    }
}
