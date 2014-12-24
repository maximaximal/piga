#pragma once

#include <string>
#include <pihud/Widget.hpp>
#include <pihud/ParticleSource.hpp>
#include <pihud/Label.hpp>
#include <pihud/Image.hpp>

namespace PiH
{
    class WeHaveAWinnerWidget : public Widget
    {
        public:
            WeHaveAWinnerWidget(Widget *parent = nullptr);
            virtual ~WeHaveAWinnerWidget();

            virtual void onUpdate(float frametime);
            virtual void onEvent(const Event &e);
            virtual void onRender(SDL_Renderer *renderer, const FloatRect &offset);

            void setWinnerName(std::string name);
            bool isDone();
            void setDone(bool done = true);
            void setStayForSeconds(float seconds);

            void setFont(std::shared_ptr<Font> font);
            void setVictoryImageTexture(std::shared_ptr<Texture> texture, const IntRect &rect);
            void setParticleTexture(std::shared_ptr<Texture> texture, const std::vector<IntRect> rects);
        protected:
            virtual void updateBoundingBox();
        private:
            std::unique_ptr<ParticleSource> m_particleSource;
            std::unique_ptr<Image> m_victoryImage;
            std::unique_ptr<Label> m_playerNameLabel;
            std::unique_ptr<Label> m_playerNameDisplayLabel;
            bool m_done = false;
            float m_time = 0;
            float m_stayForSeconds = 3;
    };
}
