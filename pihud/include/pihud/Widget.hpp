#pragma once 

#include <SDL2/SDL.h>
#include <pihud/Event.hpp>
#include <pihud/Rect.hpp>

namespace PiH
{
    class FocusManager;

    class Widget
    {
        public:
            friend class FocusManager;

            Widget(Widget *parent);
            virtual ~Widget();

            FloatRect& getBoundingBox();
            void setBoundingBox(float x, float y, float w, float h);
            void setBoundingBox(const FloatRect &box);
            void setPosition(float x, float y);
            void setWidth(float w);
            void setHeight(float h);
            virtual bool isFocused(int playerID = -1);

            virtual void onEvent(const Event &e);
            virtual void onUpdate(float frametime);
            virtual void onRender(SDL_Renderer* renderer, const FloatRect &offset);
            virtual void updateRectFromBeneath();

            void updateParent();
        protected:
            virtual void updateBoundingBox() = 0;
            
            virtual void focusGained(int playerID) = 0;
            virtual void focusLost(int playerID) = 0;

            FloatRect m_boundingBox;
            Widget *m_parent;
        private:
            bool m_currentlyUpdating = false;
            bool m_focused = false;
    };
}
