#include <pihud/Texture.hpp>

namespace PiH
{
    Texture::Texture()
    {

    }
    Texture::~Texture()
    {

    }
    const std::string &Texture::getPath()
    {
        return m_path;
    }
    SDL_Texture *Texture::getSDLTexture()
    {
        return m_texture;
    }
}
