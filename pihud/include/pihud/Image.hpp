#pragma once

#include <pihud/Widget.hpp>
#include <pihud/Texture.hpp>
#include <memory>

namespace PiH
{
    class Image : public Widget
    {
        public:
            Image(Widget *parent = nullptr);
            virtual ~Image();

            void setTexture(std::shared_ptr<Texture> texture);
            void setTextureRect(const IntRect &rect);
            virtual void onRender(SDL_Renderer *renderer, const FloatRect &offset);

            /**
             * @brief Utility function for instanced rendering.
             * @param x Position to render to (x-Coordinate)
             * @param y Position to render to (y-Coordinate)
             */
            void renderTo(float x, float y, SDL_Renderer *renderer, const FloatRect &offset);
        protected:
            virtual void updateBoundingBox();
        private:
            std::shared_ptr<Texture> m_texture;
            IntRect m_textureRect;
    };
}
