#pragma once

#include <pihud/Widget.hpp>
#include <pihud/Image.hpp>
#include <pihud/Label.hpp>
#include <sigc++/signal.h>

namespace PiH
{
    class PushButton : public Widget
    {
        public:
            PushButton(Widget *parent);
            virtual ~PushButton();

            virtual void onEvent(const Event &e);
            virtual void onUpdate(float frametime);
            virtual void onRender(SDL_Renderer *renderer, const FloatRect &offset);

            sigc::signal<void, int>& getButtonPressedSignal();
            sigc::signal<void, int>& getButtonReleasedSignal();

            void setFont(std::shared_ptr<Font> font);
            void setText(const std::string &text);
            void setTextColor(SDL_Color color);
            void setTextColor(int r, int g, int b, int a = 255);
            const std::string& getText();

            void setBackgroundTexture(std::shared_ptr<Texture> texture);
            void setNormalTextureRect(const IntRect &rect);
            void setFocusedTextureRect(const IntRect &rect);
            void setPressedTextureRect(const IntRect &rect);
        protected:
            virtual void updateBoundingBox();
            virtual void focusGained(int playerID);
            virtual void focusLost(int playerID);

            virtual void onButtonPressed(int playerID);
            virtual void onButtonReleased(int playerID);
        private:
            const IntRect& getActiveTextureRect();

            std::shared_ptr<Image> m_backgroundImage;
            std::shared_ptr<Label> m_buttonText;

            sigc::signal<void, int> m_buttonPressedSignal;
            sigc::signal<void, int> m_buttonReleasedSignal;

            IntRect m_normalTextureRect;
            IntRect m_focusedTextureRect;
            IntRect m_pressedTextureRect;

            bool m_pressed = false;
    };
}
