#include <pigaco/App.hpp>

#include <chrono>
#include <thread>

#include <easylogging++.h>

#include <pigaco/Window.hpp>
#include <pigaco/DirectoryScanner.hpp>
#include <pihud/pihud.hpp>

_INITIALIZE_EASYLOGGINGPP

namespace pigaco
{
    App::App()
    {
        LOG(INFO) << "Initializing PiGaCo app.";
    }
    App::~App()
    {
        if(m_hudContainer != nullptr)
            delete m_hudContainer;

        PiH::exit();

        m_window.reset();
    }
    void App::run()
    {
        LOG(INFO) << "Starting PiGaCo.";

        m_playerManager = std::make_shared<piga::PlayerManager>();

        auto player = std::make_shared<piga::Player>(0);
        player->setName("Unnamed 1 (0)");
        m_playerManager->set(player, 0);

        player = std::make_shared<piga::Player>(1);
        player->setName("Unnamed 2 (1)");
        m_playerManager->set(player, 1);

        m_host = std::make_shared<piga::Host>("config.yml", m_playerManager);
        m_host->init();

        m_gameInput = std::make_shared<piga::GameInput>();

        LOG(INFO) << "Clock-Precision: " << std::chrono::high_resolution_clock::period::den;

        std::chrono::time_point<std::chrono::high_resolution_clock> frameTimePointPast = std::chrono::high_resolution_clock::now();
        std::chrono::time_point<std::chrono::high_resolution_clock> frameTimePoint = std::chrono::high_resolution_clock::now();
        float frametime = 0;
        std::chrono::milliseconds desiredFrametime((long) (1 / 60.f * 1000));
        SDL_Event e;

        m_window.reset(new Window());
        m_window->init(glm::ivec2(800, 600), false);

        PiH::Config *config = new PiH::Config(m_window->getSDLRenderer());
        config->setupDefaultConfig();
        PiH::initialize(config);

        m_hudContainer = new PiH::HudContainer(0);

        m_directoryScanner.reset(new DirectoryScanner);
        m_directoryScanner->scanDirectory("Games");

        LOG(INFO) << "Starting the App-Loop.";

        while(!end())
        {
            frameTimePoint = std::chrono::high_resolution_clock::now();

            SDL_PumpEvents();
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
		if(e.type == SDL_KEYDOWN)
        {
            if(e.key.keysym.scancode == SDL_SCANCODE_B)
            {
                if(!m_directoryScanner->getGame("BomberPi")->isRunning())
                {
                    m_directoryScanner->getGame("BomberPi")->start();
                    m_host->setCurrentGameHost(m_directoryScanner->getGame("BomberPi"));
                    this->sleepWindow();
                }
            }

            if(e.key.keysym.scancode == SDL_SCANCODE_W)
            {
                m_host->setInput(0, piga::GameControl::UP, true);
            }
        }
        if(e.type == SDL_KEYUP)
        {
            if(e.key.keysym.scancode == SDL_SCANCODE_W)
            {
                m_host->setInput(0, piga::GameControl::UP, false);
            }
        }
    }
    void App::onUpdate(float frametime)
    {
        m_host->update(frametime);
        m_gameInput->update();
        m_host->applyFromGameInput(m_gameInput.get());


        m_window->glClear();
        SDL_SetRenderDrawColor(m_window->getSDLRenderer(), 0, 0, 0, 0);
        SDL_RenderClear(m_window->getSDLRenderer());

        SDL_GL_SwapWindow(m_window->getSDLWindow());
        SDL_RenderPresent(m_window->getSDLRenderer());

        if(m_isSleeping && !m_host->gameIsRunning())
        {
            wakeupWindow();
        }

        LOG_EVERY_N(60, INFO) << "Is game running: " << m_host->gameIsRunning();
    }
    bool App::end()
    {
        return m_end;
    }
    void App::sleepWindow()
    {
        m_isSleeping = true;
        m_window->deepsleep();
    }
    void App::wakeupWindow()
    {
        m_isSleeping = false;
        m_window->deepwake();
    }
    void App::setEnd(bool state)
    {
        m_end = state;
    }
    void App::onGameEvent(const piga::GameEvent &gameEvent, float frametime)
    {
        m_hudContainer->onEvent(gameEvent);
    }
}

int main()
{
    pigaco::App *app = new pigaco::App();

    app->run();

    delete app;

    return 0;
}
