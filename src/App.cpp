#include <pigaco/App.hpp>

#include <chrono>
#include <thread>

#include <easylogging++.h>

_INITIALIZE_EASYLOGGINGPP

namespace pigaco
{
    App::App()
    {
        LOG(INFO) << "Initializing PiGaCo app.";
        m_host = std::make_shared<piga::Host>();
    }
    App::~App()
    {
        if(m_hudContainer != nullptr)
            delete m_hudContainer;

        m_window.reset();
    }
    void App::run()
    {
        LOG(INFO) << "Starting PiGaCo.";
        m_host->init();

        LOG(INFO) << "Clock-Precision: " << std::chrono::high_resolution_clock::period::den;

        std::chrono::time_point<std::chrono::high_resolution_clock> frameTimePointPast = std::chrono::high_resolution_clock::now();
        std::chrono::time_point<std::chrono::high_resolution_clock> frameTimePoint = std::chrono::high_resolution_clock::now();
        float frametime = 0;
        std::chrono::milliseconds desiredFrametime((long) (1 / 60.f * 1000));
        SDL_Event e;

        m_window.reset(new Window());
        m_window->init(glm::ivec2(800, 600), true);

        m_hudContainer = new PiH::HudContainer(0);

        LOG(INFO) << "Starting the App-Loop.";

        while(!end())
        {
            frameTimePoint = std::chrono::high_resolution_clock::now();

            while(SDL_PollEvent(&e) != 0)
            {
                if(e.type == SDL_QUIT)
                {
                    setEnd(true);
                }
                onEvent(e, frametime);
            }
            onUpdate(frametime);

            frametime = std::chrono::duration_cast<std::chrono::milliseconds>(frameTimePoint - frameTimePointPast).count();

            if(frametime < desiredFrametime.count())
                std::this_thread::sleep_for(desiredFrametime - std::chrono::duration_cast<std::chrono::milliseconds>(frameTimePoint - frameTimePointPast));

            frameTimePointPast = frameTimePoint;
        }
    }
    void App::onEvent(const SDL_Event &e, float frametime)
    {

    }
    void App::onUpdate(float frametime)
    {
        m_window->glClear();
        SDL_SetRenderDrawColor(m_window->getSDLRenderer(), 0, 0, 0, 0);
        SDL_RenderClear(m_window->getSDLRenderer());

        SDL_GL_SwapWindow(m_window->getSDLWindow());
        SDL_RenderPresent(m_window->getSDLRenderer());
    }
    bool App::end()
    {
        return m_end;
    }
    void App::setEnd(bool state)
    {
        m_end = state;
    }
}

int main()
{
    pigaco::App *app = new pigaco::App();

    app->run();

    delete app;

    return 0;
}
