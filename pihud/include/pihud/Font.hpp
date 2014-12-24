#pragma once

#include <SDL2/SDL_ttf.h>
#include <string>

namespace PiH
{
    class Font
    {
        public:
            Font();
            virtual ~Font();

            virtual void load(const std::string &fontPath);
            virtual TTF_Font* getFont();
            virtual int getPtSize();
        private:
            TTF_Font *m_font = nullptr;
            int m_ptSize = 16;
    };
}
