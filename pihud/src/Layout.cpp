#include <pihud/Layout.hpp>

namespace PiH
{
    Layout::Layout(Widget *parent)
    	: Widget(parent)
    {

    }
    Layout::~Layout()
    {

    }
    void Layout::setLayouter(const Layouter &layouter)
    {
        m_layouter = layouter;
    }
    void Layout::updateLayout()
    {
        m_layouter.setBoundingBox(getBoundingBox());
        m_layouter.setBoxes(m_widgets);
    }
}
