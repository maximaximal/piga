#pragma once

#include <pihud/Widget.hpp>

#include <vector>
#include <memory>
#include <random>
#include <pihud/Particle.hpp>

namespace PiH
{
    class ParticleSource : public Widget
    {
        public:
            ParticleSource(Widget *parent);
            virtual ~ParticleSource();

            void setTargetCount(long count);
            void setTexture(std::shared_ptr<Texture> texture);
            void setTextureRectVector(const std::vector<IntRect> &textureRects);
            void setDuration(float time);
            void setGravity(float gravity);
            void setSpawnsPerFrame(float count);

            void setXSpeedRange(float min, float max);
            void setYSpeedRange(float min, float max);
            void setRotationSpeedRange(float min, float max);
            void setXStartRange(float min, float max);
            void setYStartRange(float min, float max);

            inline bool isFinished();

            virtual void onUpdate(float frametime);
            virtual void onEvent(const Event &e);
            virtual void onRender(SDL_Renderer *renderer, const FloatRect &offset);
        protected:
            void addParticle();
            inline bool spawnMoreParticles();
        private:
            std::vector<std::unique_ptr<Particle> > m_particles;
            std::shared_ptr<Texture> m_texture;
            std::vector<IntRect> m_textureRects;
            float m_duration = 0;
            float m_time = 0;
            float m_targetCount = 30;
            float m_gravity = 9.81;
            float m_spawnsPerFrame = 1;
            float m_currentFrameSpawns = 0;

            std::default_random_engine m_generator;
            std::uniform_int_distribution<int> m_distribution;

            std::uniform_real_distribution<float> m_xSpeedRange;
            std::uniform_real_distribution<float> m_ySpeedRange;
            std::uniform_real_distribution<float> m_rotationSpeedRange;
            std::uniform_real_distribution<float> m_xStartRange;
            std::uniform_real_distribution<float> m_yStartRange;
    };
}
