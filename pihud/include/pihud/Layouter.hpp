#pragma once

#include <memory>
#include <map>

#include <pihud/Widget.hpp>

namespace PiH
{
    class Layouter : public Widget
    {
        public:
            typedef std::map<FloatRect, std::shared_ptr<Widget> > LayoutedWidgetsMap;

            Layouter(Widget *parent = 0);
            Layouter(const Layouter &layouter, Widget *parent = 0);
            virtual ~Layouter();

            virtual void setBoxes(LayoutedWidgetsMap &widgets);
    };
}
