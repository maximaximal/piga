#pragma once

#include <memory>
#include <pihud/Widget.hpp>
#include <pihud/Texture.hpp>

namespace PiH
{
    /**
     * @brief The Particle class represents a single particle.
     *
     * These particles are not intended for heavy usage, as they should contain
     * graphics and only be on the GUI level.
     *
     * Particles can have trailing particles too. They mostly are derived from the parent particle
     * and have the same texture, but are a little bit different in behavior.
     */
    class Particle
    {
        public:
            Particle();
            ~Particle();

            float velX = 5;
            float velY = 5;

            float drag = 5;

            void setX(float x);
            void setY(float y);
            float getX();
            float getY();

            void setTextureRect(const IntRect &rect);

            float rotation = 0;
            float rotationSpeed = 10;

            void onUpdate(float frametime, float gravity = 0);
            void onRender(SDL_Renderer *renderer);

            std::shared_ptr<Texture> texture;

            const IntRect& getCurrentDstRect();
            const IntRect &getTextureRect();
        private:
            bool m_deletionPending = false;
            FloatRect m_dstRect;
            IntRect m_srcRect;
    };
}
