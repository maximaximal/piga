#pragma once

#include <pihud/Widget.hpp>
#include <pihud/Image.hpp>
#include <pihud/Rect.hpp>
#include <vector>

namespace PiH
{
    /**
     * @brief The IconHealthIndicator class describes a graphical health indicator using icons.
     *
     * An example would be the hears-lifebar in some games (like in zelda).
     */
    class IconHealthIndicator : public Widget
    {
        public:
            IconHealthIndicator(Widget *parent = nullptr);
            virtual ~IconHealthIndicator();

            int getCurrentHealth();
            int getMaximumHealth();

            void setCurrentHealth(int health);
            void setMaximumHealth(int maximumHealth);

            void setFullIcon(const IntRect &rect);
            void setDepletedIcon(const IntRect &rect);
            void setSideOfIcons(Direction side);

            void setTexture(std::shared_ptr<Texture> texture);

            virtual void onEvent(const Event &e);
            virtual void onRender(SDL_Renderer *renderer, const FloatRect &offset);
        protected:
            void updateMaximum();
            void updateCurrent();
            void updateTexture();

            virtual void updateBoundingBox();
            
            virtual void focusGained(int playerID) {}
            virtual void focusLost(int playerID) {}
        private:
            void updateDimensions();

            int m_currentHealth = 0;
            int m_maximumHealth = 0;
            Direction m_sideOfIcons = LEFT;
            std::vector<std::unique_ptr<Image> > m_icons;
            std::shared_ptr<Texture> m_texture;
            IntRect m_fullIcon;
            IntRect m_depletedIcon;
    };
}
