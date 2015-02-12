#include <pihud/Image.hpp>

#include <iostream>
using std::cout;
using std::endl;

namespace PiH
{
    Image::Image(Widget *parent)
    	: Widget(parent)
    {

    }
    Image::~Image()
    {

    }
    void Image::setTexture(std::shared_ptr<Texture> texture)
    {
        m_texture = texture;
    }
    void Image::setTextureRect(const IntRect &rect)
    {
        m_textureRect = rect;
        m_boundingBox.w = rect.w;
        m_boundingBox.h = rect.h;
    }
    void Image::onEvent(const Event &e)
    {

    }
    void Image::onRender(SDL_Renderer *renderer, const FloatRect &offset)
    {
        SDL_Rect srcRect = m_textureRect.toSDLRect();
        SDL_Rect dstRect = m_boundingBox.toSDLRect();

        if(m_texture)
            SDL_RenderCopy(renderer, m_texture->getSDLTexture(), &srcRect, &dstRect);
    }
    void Image::renderTo(float x, float y, SDL_Renderer *renderer, const FloatRect &offset)
    {
        SDL_Rect srcRect = m_textureRect.toSDLRect();
        SDL_Rect dstRect = m_boundingBox.toSDLRect();

        dstRect.x = x;
        dstRect.y = y;

        if(m_texture)
            SDL_RenderCopy(renderer, m_texture->getSDLTexture(), &srcRect, &dstRect);
    }
    void Image::updateBoundingBox()
    {

    }
}
