#pragma once

#include <vector>
#include <pihud/Widget.hpp>
#include <pihud/Image.hpp>
#include <pihud/Label.hpp>

namespace PiH
{
    class QueueDisplayWidget : public Widget
    {
        public:
            QueueDisplayWidget(std::size_t queueSize, Widget *parent);
            virtual ~QueueDisplayWidget();
            void clear();

            virtual void onEvent(const Event &e);
            virtual void onUpdate(float frametime);
            virtual void onRender(SDL_Renderer *renderer, const FloatRect &offset);

            void pushImage(std::unique_ptr<Image> image);
            void setBackgroundImage(std::unique_ptr<Image> image);
            void setQueueSize(std::size_t size);

            std::size_t getQueueSize();
        protected:
            virtual void updateBoundingBox();
            virtual void focusGained(int playerID) {}
            virtual void focusLost(int playerID) {}
        private:
            std::vector<std::unique_ptr<Image> > m_images;
            std::unique_ptr<Image> m_backgroundImage;
            std::size_t m_queueSize = 3;
    };
}
