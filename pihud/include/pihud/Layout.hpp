#pragma once

#include <pihud/Widget.hpp>
#include <pihud/Layouter.hpp>

namespace PiH
{
    class Layout : public Widget
    {
        public:
            Layout(Widget *parent = 0);
            virtual ~Layout();

            void setLayouter(const Layouter &layouter);
            void updateLayout();
        protected:
            Layouter m_layouter;
            Layouter::LayoutedWidgetsMap m_widgets;
    };
}
