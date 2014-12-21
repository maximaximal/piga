#include <piga/Renderer.hpp>

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

namespace piga
{
    Renderer::Renderer(SDL_Window *window, SDL_Renderer *sdlRenderer)
    	: m_sdlWindow(window), m_sdlRenderer(sdlRenderer)
    {

    }
    Renderer::~Renderer()
    {

    }
    void Renderer::render()
    {
        if(m_sdlRenderer != nullptr)
        {
			SDL_RenderPresent(getSDLRenderer());
        }
    }
    void Renderer::setSDLRenderer(SDL_Renderer *renderer)
    {
        m_sdlRenderer = renderer;
    }
    void Renderer::setSDLWindow(SDL_Window *window)
    {
        m_sdlWindow = window;
    }
    SDL_Renderer *Renderer::getSDLRenderer()
    {
        return m_sdlRenderer;
    }
    SDL_Window *Renderer::getSDLWindow()
    {
		return m_sdlWindow;
    }
}
