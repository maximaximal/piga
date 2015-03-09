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

        if(m_centered)
        {
            dstRect.x += dstRect.w / 2 - m_textW / 2;
            dstRect.y += dstRect.h / 2 - m_textH / 2;
        }

        dstRect.w = m_textW;
        dstRect.h = m_textH;

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
    void Label::setColor(int r, int g, int b, int a)
    {
        m_color.r = r;
        m_color.g = g;
        m_color.b = b;
        m_color.a = a;
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

            SDL_QueryTexture(m_renderedText, nullptr, nullptr, &m_textW, &m_textH);

            updateParent();
        }
    }
    void Label::setCentered(bool centered)
    {
        m_centered = centered;
    }
    int Label::getTextWidth()
    {
        return m_textW;
    }
    int Label::getTextHeight()
    {
        return m_textH;
    }
    const std::string& Label::getText()
    {
        return m_text;
    }
}
