#ifndef LIBPIGA_PIGA_RENDERER_HPP_INCLUDED
#define LIBPIGA_PIGA_RENDERER_HPP_INCLUDED

struct SDL_Renderer;
struct SDL_Window;

namespace piga
{
    class Renderer
    {
        public:
            Renderer(SDL_Window *window = nullptr, SDL_Renderer *sdlRenderer = nullptr);
            virtual ~Renderer();

            void render();

            void setSDLRenderer(SDL_Renderer *renderer);
            void setSDLWindow(SDL_Window *window);

            SDL_Renderer* getSDLRenderer();
            SDL_Window* getSDLWindow();
        private:
            SDL_Renderer *m_sdlRenderer = nullptr;
            SDL_Window *m_sdlWindow = nullptr;
    };
}

#endif
