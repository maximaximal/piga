#include <pigaco/Window.hpp>
#include <easylogging++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace pigaco
{
    Window::Window()
    {
		LOG(INFO) << "Creating Window.";
        m_renderer = nullptr;
    }
    Window::~Window()
    {
        if(m_SDLImageInitialized)
            IMG_Quit();
        if(TTF_WasInit())
            TTF_Quit();
        if(m_SDLInitialized)
			SDL_Quit();

		LOG(INFO) << "Deleted Window.";
    }
    int Window::init(const glm::ivec2 &windowSize, bool fullscreen)
    {
        m_windowSize = windowSize;
        m_fullscreen = fullscreen;

		LOG(INFO) << "Initializing Window (" << windowSize.x << "x" << windowSize.y << ")";
		if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			LOG(FATAL) << "SDL_Init fauled! Error: " << SDL_GetError();
			return 1;
		}
		m_SDLInitialized = true;

        if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
        {
            LOG(FATAL) << "IMG_Init failed! Error: " << IMG_GetError();
            return 1;
        }
        m_SDLImageInitialized = true;

        if(TTF_Init() == -1)
        {
			LOG(FATAL) << "TTF_Init failed! Error: " << TTF_GetError();
			return 1;
        }

        Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
        if(fullscreen)
            flags = flags | SDL_WINDOW_FULLSCREEN_DESKTOP;

		m_window = SDL_CreateWindow("PiGaCo - Console Host", 100, 100, windowSize.x, windowSize.y, flags);
		if(m_window == nullptr)
		{
			LOG(FATAL) << "SDL_CreateWindow failed! Error: " << SDL_GetError();
			return 1;
		}
        m_glContext = SDL_GL_CreateContext(m_window);

        //Load required functions for the window class.
        m_glClear = SDL_GL_GetProcAddress("glClear");
        m_glClearColor = SDL_GL_GetProcAddress("glClearColor");

        if(m_glClear == nullptr)
        {
            LOG(WARNING) << "The OpenGL-Function \"glClear\" has not been received!";
        }
        if(m_glClearColor == nullptr)
        {
            LOG(WARNING) << "The OpenGL-Function \"glClearColor\" has not been received!";
        }

        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
        if(m_renderer == nullptr)
        {
            LOG(FATAL) << "SDL_CreateRenderer failed! Error: " << SDL_GetError();
            return 1;
        }


        return 0;
    }
    void Window::onEvent(const SDL_Event &e)
    {

    }
    glm::ivec2 Window::getSize()
    {
        int x, y;
        SDL_GetWindowSize(m_window, &x, &y);
        return glm::ivec2(x, y);
    }
    void Window::glClear()
    {
        if(m_glClear != nullptr && m_glClearColor != nullptr)
        {
            ((GLFunction_ClearColor) m_glClearColor)(0, 0, 0, 1);
            ((GLFunction_Clear) m_glClear)(m_window);
        }
    }
    void Window::deepsleep()
    {
		this->destroy();
    }
    void Window::deepwake()
    {
        this->init(m_windowSize, m_fullscreen);
    }
    void Window::hide()
    {
        SDL_SetWindowFullscreen(m_window, 0);
    }
    void Window::show()
    {
        SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }
    void Window::destroy()
    {
		// Clean the SDL objects.
		if(m_window != nullptr)
        {
			SDL_DestroyWindow(m_window);
            SDL_GL_DeleteContext(m_glContext);
            m_window = nullptr;
        }
        if(m_renderer != nullptr)
        {
            SDL_DestroyRenderer(m_renderer);
            m_renderer = nullptr;
        }
    }
    SDL_Renderer *Window::getSDLRenderer()
    {
        return m_renderer;
    }
    SDL_Window *Window::getSDLWindow()
    {
        return m_window;
    }
}
