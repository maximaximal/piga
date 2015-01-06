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

            void destroy();
        private:
            TTF_Font *m_font = nullptr;
            std::string m_fontPath;
            std::string m_fontID;
            int m_ptSize = 16;
    };
}
