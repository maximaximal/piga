#include <pigaco/App.hpp>

#include <chrono>
#include <thread>

#include <pigaco/Window.hpp>
#include <pigaco/DirectoryScanner.hpp>
#include <pigaco/GameChooser.hpp>
#include <pihud/pihud.hpp>
#include <pihud/VerticalListLayout.hpp>
#include <pihud/ParticleSource.hpp>

#define ELPP_NO_DEFAULT_LOG_FILE
#include <../../include/easylogging++.h>

INITIALIZE_EASYLOGGINGPP

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
        m_window->init(glm::ivec2(800, 600), true);

        PiH::Config *config = new PiH::Config(m_window->getSDLRenderer());
        config->setupDefaultConfig();
        PiH::initialize(config);

        m_textureManager = std::make_shared<PiH::TextureManager>(m_window->getSDLRenderer());
        m_fontManager = std::make_shared<PiH::FontManager>();
        
        m_hudContainer = new PiH::HudContainer(0);
        m_hudContainer->setBoundingBox(0, 0, m_window->getSize().x, m_window->getSize().y);

        m_directoryScanner = std::make_shared<DirectoryScanner>();
        m_directoryScanner->scanDirectory("Games");

        PiH::ParticleSource *particles = new PiH::ParticleSource(m_hudContainer);
        particles->setDuration(0);
        particles->setGravity(-0.0001);
        particles->setSpawnsPerFrame(0.3);
        particles->setTargetCount(m_window->getSize().x * m_window->getSize().y / 300);
        particles->setTexture(m_textureManager->getTexture("Data/Textures/GuiBackgroundEffects.png"));
        particles->setXSpeedRange(-0.25, 0.25);
        particles->setYSpeedRange(0.00005, 0.00007);
        particles->setRotationSpeedRange(0, 0);
        
        std::vector<PiH::IntRect> rects = {
            PiH::IntRect(0, 0, 128, 128),
            PiH::IntRect(133, 37, 80, 80),
            PiH::IntRect(0, 125, 400, 320)
        };
        
        particles->setTextureRectVector(rects);
        particles->setBoundingBox(m_hudContainer->getBoundingBox());
        particles->setXStartRange(0, m_window->getSize().x);
        particles->setYStartRange(-400, -401);
        m_hudContainer->addWidget(particles, "GuiBackgroundEffects");
        
        GameChooser *chooser = new GameChooser(m_hudContainer);
        chooser->setFont(m_fontManager->get("Data/Fonts/Roboto-Regular.ttf:22"));
        chooser->setTextureManager(m_textureManager);
        chooser->setDirectoryScanner(m_directoryScanner);
        
        PiH::VerticalListLayout *verticalLayout = new PiH::VerticalListLayout;
        verticalLayout->setSpacing(10);
        chooser->setLayouter(verticalLayout);
        
        chooser->setBoundingBox(PiH::FloatRect(0, m_window->getSize().y / 4, m_window->getSize().x, m_window->getSize().y / 2));
        
        m_hudContainer->addWidget(chooser, "GameChooser");
        

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
        
        if(!m_isSleeping)
        {
            m_hudContainer->onUpdate(frametime);
        }

        m_window->glClear();
        SDL_SetRenderDrawColor(m_window->getSDLRenderer(), 0, 0, 0, 0);
        SDL_RenderClear(m_window->getSDLRenderer());

        m_hudContainer->onRender(m_window->getSDLRenderer(), PiH::FloatRect(0, 0, m_window->getSize().x, m_window->getSize().y));
        SDL_RenderPresent(m_window->getSDLRenderer());
        
        if(m_isSleeping && !m_host->gameIsRunning())
        {
            wakeupWindow();
        }
    }
    bool App::end()
    {
        return m_end;
    }
    void App::sleepWindow()
    {
        m_isSleeping = true;
        m_window->hide();
    }
    void App::wakeupWindow()
    {
        m_isSleeping = false;
        m_window->show();
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

int main(int argv, char* argc[])
{
    START_EASYLOGGINGPP(argv, argc);

    el::Configurations conf;

    conf.setToDefault();
    conf.setGlobally(el::ConfigurationType::ToFile, "false");

    el::Loggers::reconfigureAllLoggers(conf);

    pigaco::App *app = new pigaco::App();

    app->run();

    delete app;

    return 0;
}
