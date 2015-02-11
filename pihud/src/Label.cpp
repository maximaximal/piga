#include <pihud/Label.hpp>
#include <pihud/pihud.hpp>

#include <iostream>
using std::cout;
using std::endl;

namespace PiH
{
    Label::Label(Widget *parent)
        : Widget(parent)
    {

    }
    Label::~Label()
    {
        if(m_renderedText != nullptr)
        {
            SDL_DestroyTexture(m_renderedText);
        }
    }
    void Label::onEvent(const Event &e)
    {

    }
    void Label::onUpdate(float frametime)
    {

    }
    void Label::onRender(SDL_Renderer *renderer, const FloatRect &offset)
    {
        SDL_Rect dstRect = m_boundingBox.toIntRect().toSDLRect();

        if(m_renderedText != nullptr)
        {
            SDL_RenderCopy(renderer, m_renderedText, nullptr, &dstRect);
        }
    }
    void Label::setText(const std::string &text)
    {
        m_text = text;
        redraw();
    }
    void Label::setFont(std::shared_ptr<Font> font)
    {
        m_font = font;
        redraw();
    }
    void Label::setColor(SDL_Color color)
    {
        m_color = color;
        redraw();
    }
    void Label::updateBoundingBox()
    {
        redraw();
    }
    void Label::redraw()
    {
        if(m_font && m_text.length() > 0)
        {
            if(m_renderedText != nullptr)
            {
                SDL_DestroyTexture(m_renderedText);
            }
            SDL_Surface *rendered = nullptr;

            if(getBoundingBox().w == 0)
            {
                rendered = TTF_RenderUTF8_Blended(m_font->getFont(), m_text.c_str(), m_color);
            }
            else
            {
                rendered = TTF_RenderUTF8_Blended_Wrapped(m_font->getFont(), m_text.c_str(), m_color, getBoundingBox().w);
            }

            if(rendered == nullptr)
            {
                cout << "Problem rendering text to surface: " << TTF_GetError() << endl;
            }
            m_renderedText = SDL_CreateTextureFromSurface(getGlobalConfig()->getSDLRenderer(), rendered);
            if(m_renderedText == nullptr)
            {
                cout << "Problem rendering text to texture: " << SDL_GetError() << endl;
            }
            SDL_FreeSurface(rendered);

            int w = 0, h = 0;
            SDL_QueryTexture(m_renderedText, nullptr, nullptr, &w, &h);

            m_boundingBox.w = w;
            m_boundingBox.h = h;

            updateParent();
        }
    }
}
