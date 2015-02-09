#pragma once

#include <map>
#include <memory>
#include <string>

#include <pihud/Texture.hpp>

namespace PiH
{
    class TextureManager
    {
    public:
        TextureManager(SDL_Renderer *renderer);
        virtual ~TextureManager();
        
        std::shared_ptr<Texture> getTexture(const std::string &id);
    private:
        std::map<std::string, std::weak_ptr<Texture>> m_textures;
        SDL_Renderer *m_renderer = nullptr;
    };
}