#include <pihud/Particle.hpp>

namespace PiH
{
    Particle::Particle()
    {

    }
    Particle::~Particle()
    {

    }
    void Particle::setX(float x)
    {
        m_dstRect.x = x;
    }
    void Particle::setY(float y)
    {
        m_dstRect.y = y;
    }
    float Particle::getX()
    {
        return m_dstRect.x;
    }
    float Particle::getY()
    {
        return m_dstRect.y;
    }
    void Particle::setTextureRect(const IntRect &rect)
    {
        m_srcRect = rect;
        m_dstRect.w = rect.w;
        m_dstRect.h = rect.h;
    }
    void Particle::onUpdate(float frametime, float gravity)
    {
        velY -= gravity;
        m_dstRect.x += velX * frametime * 2;
        m_dstRect.y += velY * frametime * 2;
        rotation += rotationSpeed * frametime;
    }
    void Particle::onRender(SDL_Renderer *renderer)
    {
        if(texture)
        {
            SDL_Rect srcRect = m_srcRect.toSDLRect();
            SDL_Rect dstRect = m_dstRect.toSDLRect();
            SDL_RenderCopyEx(renderer, texture->getSDLTexture(), &srcRect, &dstRect, rotation, nullptr, SDL_FLIP_NONE);
        }
    }
    const IntRect &Particle::getTextureRect()
    {
        return m_srcRect;
    }
}
