#pragma once

#include <pihud/Widget.hpp>
#include <pihud/Texture.hpp>
#include <pihud/Font.hpp>
#include <pihud/IconHealthIndicator.hpp>
#include <pihud/Label.hpp>

namespace PiH
{
    class HealthAndNameDisplay : public Widget
    {
        public:
            HealthAndNameDisplay(Widget *parent = nullptr);
            virtual ~HealthAndNameDisplay();

            void setTexture(std::shared_ptr<Texture> texture);
            void setFont(std::shared_ptr<Font> font);
            void setName(std::string text);
            void setDistance(int distance);
            void setCurrentHealth(int health);
            void setSideOfIcons(PiH::Direction side);

            IconHealthIndicator* getHealthIndicator();
            Label* getLabel();

            virtual void onEvent(const Event &e);
            virtual void onRender(SDL_Renderer *renderer, const FloatRect &offset);
        protected:
            virtual void updateRectFromBeneath();
            virtual void updateBoundingBox();
        private:
            IconHealthIndicator *m_iconHealthIndicator;
            Label *m_label;
            PiH::Direction m_sideOfIcons;

            int m_distance = 5;
    };
}
