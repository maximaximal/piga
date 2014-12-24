#pragma once

#include <SDL2/SDL.h>
#include <string>

namespace PiH
{
    class Texture
    {
        public:
            Texture();
            virtual ~Texture();

            virtual const std::string& getPath();
			virtual SDL_Texture* getSDLTexture();
        private:
           	SDL_Texture *m_texture;
            std::string m_path;
    };
}
