#pragma once

#include <string>
#include <map>
#include <pihud/Widget.hpp>

namespace PiH
{
    class HudContainer : public Widget
    {
        public:
            HudContainer(Widget *parent);
            virtual ~HudContainer();
            void clear();

            virtual void onEvent(const Event &e);
            virtual void onUpdate(float frametime);
            virtual void onRender(SDL_Renderer *renderer, const FloatRect &offset);

            virtual void updateRectFromBeneath();

            std::shared_ptr<Widget> getWidget(const std::string &name);
            void addWidget(std::shared_ptr<Widget> widget, std::string name = "");
            void deleteWidget(const std::string &name);
        protected:
            virtual void updateBoundingBox();
            virtual void focusGained(int playerID) {}
            virtual void focusLost(int playerID) {}
        private:
            std::map<std::string, std::shared_ptr<Widget>> m_widgets;
    };
}
