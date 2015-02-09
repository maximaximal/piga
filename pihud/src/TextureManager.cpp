#include <pihud/TextureManager.hpp>

namespace PiH
{
    TextureManager::TextureManager(SDL_Renderer *renderer)
        : m_renderer(renderer)
    {

    }
    TextureManager::~TextureManager()
    {
        for(auto texture : m_textures)
        {
            if(!texture.second.expired())
            {
                auto sharedTexture = texture.second.lock();
                sharedTexture.reset();
            }
        }
        m_textures.clear();
    }
    std::shared_ptr<Texture> TextureManager::getTexture(const std::string &id)
    {
        if(m_textures.count(id) == 0)
        {
            std::shared_ptr<Texture> texture = std::make_shared<Texture>();
            texture->load(m_renderer, id);
            m_textures[id] = texture;
            return texture;
        }
        return m_textures[id].lock();
    }
}