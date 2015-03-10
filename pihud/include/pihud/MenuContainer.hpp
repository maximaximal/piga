#pragma once

#include <map>
#include <string>

#include <pihud/HudContainer.hpp>

namespace PiH
{
    class MenuContainer : public Widget
    {
        public:
            MenuContainer(Widget *parent = nullptr);
            virtual ~MenuContainer();

            virtual void onEvent(const Event &e);
            virtual void onUpdate(float frametime);
            virtual void onRender(SDL_Renderer *renderer, const FloatRect &offset);

            virtual void updateRectFromBeneath();

            void setCurrentPage(const std::string &pageName);
            std::shared_ptr<HudContainer> getCurrentPage();

            void addPage(std::shared_ptr<HudContainer> page, const std::string &pageName);
            void removePage(const std::string &pageName);
        protected:
            virtual void updateBoundingBox();

            virtual void focusGained(int playerID);
            virtual void focusLost(int playerID);
        private:
			std::map<std::string, std::shared_ptr<HudContainer>> m_pages;
            std::shared_ptr<HudContainer> m_currentPage;
    };
}
