#pragma once 

#include <SDL2/SDL.h>
#include <pihud/Event.hpp>
#include <pihud/Rect.hpp>

namespace PiH
{
    class Widget
    {
        public:
            Widget(Widget *parent);
            virtual ~Widget();

            FloatRect& getBoundingBox();
            void setBoundingBox(const FloatRect &box);
            void setPosition(float x, float y);

            virtual void onEvent(const Event &e);
            virtual void onUpdate(float frametime);
            virtual void onRender(SDL_Renderer* renderer, const FloatRect &offset);
            virtual void updateRectFromBeneath();

            void updateParent();
        protected:
            virtual void updateBoundingBox();

            FloatRect m_boundingBox;
            Widget *m_parent;
        private:
            bool m_currentlyUpdating = false;
    };
}
