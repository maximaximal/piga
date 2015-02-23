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

            void setLayouter(Layouter *layouter);
            void updateLayout();
            void addWidget(std::shared_ptr<Widget> widget);
            void removeWidget(std::shared_ptr<Widget> widget);

            virtual void onEvent(const Event &e);
            virtual void onUpdate(float frametime);
            virtual void onRender(SDL_Renderer *renderer, const FloatRect &offset);
        protected:
            Layouter *m_layouter = nullptr;
            Layouter::LayoutedWidgets m_widgets;

            virtual void updateBoundingBox();
            virtual void focusGained(int playerID) {}
            virtual void focusLost(int playerID) {}
    };
}
