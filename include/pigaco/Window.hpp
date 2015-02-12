#ifndef CLIENT_WINDOW_HPP_INCLUDED
#define CLIENT_WINDOW_HPP_INCLUDED

#include <glm/vec2.hpp>
#include <SDL2/SDL.h>

namespace pigaco
{
    class Window 
    {
	public:
	    Window();
	    virtual ~Window();
	    
	    /**
	     * @brief Initialize the window.
	     * 
	     * Creates the SDL_Window and all required SDL structs. 
	     * 
	     * @param windowSize The size the SDL Window should have. 
	     */
	    int init(const glm::ivec2 &windowSize, bool fullscreen);
	    
	    SDL_Renderer* getSDLRenderer();
	    SDL_Window* getSDLWindow();

        void onEvent(const SDL_Event &e);

        glm::ivec2 getSize();

        void glClear();

        void deepsleep();
        void deepwake();
        
        void hide();
        void show();

        void destroy();
    private:
        typedef void (*GLFunction_ClearColor)(float , float, float, float);
        typedef void (*GLFunction_Clear)(SDL_Window*);

	    SDL_Window *m_window = nullptr;
        SDL_Renderer *m_renderer = nullptr;
        SDL_GLContext m_glContext;
	    
	    bool m_SDLInitialized = false;
        bool m_SDLImageInitialized = false;

        void* m_glClearColor = nullptr;
        void* m_glClear = nullptr;

        glm::ivec2 m_windowSize;
       	bool m_fullscreen;
    };
}

#endif
