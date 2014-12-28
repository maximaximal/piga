#pragma once

#include <memory>
#include <vector>

#include <pihud/Widget.hpp>

namespace PiH
{
    class Layout;

    class Layouter : public Widget
    {
        public:
            friend class Layout;
            typedef std::vector<std::shared_ptr<Widget> > LayoutedWidgets;

            Layouter(Widget *parent = 0);
            Layouter(const Layouter &layouter, Widget *parent = 0);
            virtual ~Layouter();

            virtual void onUpdate(float frametime);
            virtual void onEvent(const Event &e);
            virtual void onRender(SDL_Renderer *renderer, const FloatRect &offset);

            virtual void setBoxes(LayoutedWidgets &widgets);
        protected:
            LayoutedWidgets *m_widgets = nullptr;
    };
}
