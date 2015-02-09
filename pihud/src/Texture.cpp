#include <pihud/Texture.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <easylogging++.h>

namespace PiH
{
    Texture::Texture()
    {

    }
    Texture::~Texture()
    {
        destroy();
    }
    int Texture::load(SDL_Renderer *renderer, const std::string &path)
    {
        destroy();
        m_path = path;
        
        m_texture = IMG_LoadTexture(renderer, path.c_str());
        if(m_texture == nullptr)
        {
            LOG(INFO) << "Could not load texture \"" << path << "\" because of an error: " << IMG_GetError();
            return 1;
        }
        return 0;
    }
    void Texture::destroy()
    {
        if(m_texture != nullptr)
        {
            SDL_DestroyTexture(m_texture);
            m_texture = nullptr;
        }
    }
    const std::string& Texture::getPath()
    {
        return m_path;
    }
    SDL_Texture* Texture::getSDLTexture()
    {
        return m_texture;
    }
}
