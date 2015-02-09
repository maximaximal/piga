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

            int load(SDL_Renderer *renderer, const std::string &path);
            void destroy();

            virtual const std::string& getPath();
            virtual SDL_Texture* getSDLTexture();
        private:
            SDL_Texture *m_texture = nullptr;
            SDL_Renderer *m_renderer = nullptr;
            std::string m_path = "";
    };
}
