#pragma once

#include <pihud/Widget.hpp>
#include <pihud/Font.hpp>
#include <memory>
#include <SDL2/SDL_ttf.h>
#include <string>

namespace PiH
{
    class Label : public Widget
    {
        public:
            Label(Widget *parent);
            virtual ~Label();

            virtual void onEvent(const Event &e);
            virtual void onUpdate(float frametime);
            virtual void onRender(SDL_Renderer *renderer, const FloatRect &offset);

            void setText(const std::string &text);
            void setFont(std::shared_ptr<Font> font);
            void setColor(SDL_Color color);
            void setColor(int r, int g, int b, int a = 255);
            void redraw();
            void setCentered(bool centered = true);

            int getTextWidth();
            int getTextHeight();

            const std::string& getText();
        protected: 
            virtual void updateBoundingBox();
            virtual void focusGained(int playerID) {}
            virtual void focusLost(int playerID) {}
        private:
            std::string m_text;
            std::shared_ptr<Font> m_font;
            SDL_Texture *m_renderedText = nullptr;
            SDL_Color m_color;
            bool m_centered = false;
            int m_textW, m_textH;
    };
}
