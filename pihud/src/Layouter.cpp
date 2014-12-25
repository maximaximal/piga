#include <pihud/Layouter.hpp>

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
    void Layouter::setBoxes(LayoutedWidgetsMap &widgets)
    {
        //Default layout: All child-widgets have the same bounding box like the layouter.
        for(auto &widget : widgets)
        {
            widget.second->setBoundingBox(getBoundingBox());
        }
    }
}
