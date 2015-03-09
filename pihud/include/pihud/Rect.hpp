#pragma once

#include <SDL2/SDL_rect.h>
#include <iostream>

namespace PiH
{
    template<typename T>
    class Rect
    {
        public:
            Rect() {
                clear();
            }

            Rect(T x, T y) {
                clear();
                this->x = x;
                this->y = y;
            }

            Rect(T x, T y, T w, T h) {
                this->x = x;
                this->y = y;
                this->w = w;
                this->h = h;
            }
            Rect(const SDL_Rect &sdlRect) {
                fromSDLRect(sdlRect);
            }
            ~Rect() {

            }
            void clear() {
                x = 0;
                y = 0;
                w = 0;
                h = 0;
            }
            const SDL_Rect& toSDLRect() {
                m_sdlRect.x = x;
                m_sdlRect.y = y;
                m_sdlRect.w = w;
                m_sdlRect.h = h;
                return m_sdlRect;
            }
            void toSDLRect(SDL_Rect &rect) {
                rect.x = x;
                rect.y = y;
                rect.w = w;
                rect.h = h;
            }

            void fromSDLRect(const SDL_Rect &sdlRect) {
                this->x = sdlRect.x;
                this->y = sdlRect.y;
                this->w = sdlRect.w;
                this->h = sdlRect.h;
            }
            Rect<int32_t> toIntRect() {
                Rect<int32_t> rect;
                rect.x = x;
                rect.y = y;
                rect.w = w;
                rect.h = h;
                return rect;
            }

            T x;
            T y;
            T w;
            T h;

            void print() {
                std::cout << "Rect-Print: " << x << "x" << y << "x" << w << "x" << h << "x" << std::endl;
            }
        private:
            /**
             * @brief Caches SDL-Rects to minify memory assignments.
             */
            SDL_Rect m_sdlRect;
    };

    typedef Rect<float> FloatRect;
    typedef Rect<int32_t> IntRect;
}

inline bool operator==(const PiH::FloatRect &l, const PiH::FloatRect &r)
{
    return !(l == r);
}
inline bool operator!=(const PiH::FloatRect &l, const PiH::FloatRect &r)
{
    if(l.x == r.x
            && l.y == r.y
            && l.w == r.w
            && l.h == r.h)
    {
        return true;
    }
    return false;
}
