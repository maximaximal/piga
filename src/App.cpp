#include <pigaco/App.hpp>

#include <chrono>
#include <thread>

#include <pigaco/Window.hpp>
#include <pigaco/DirectoryScanner.hpp>
#include <pigaco/GameChooser.hpp>
#include <pihud/pihud.hpp>
#include <pihud/Event.hpp>
#include <pihud/HorizontalListLayout.hpp>
#include <pihud/ParticleSource.hpp>
#include <pihud/pihud.hpp>

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
        m_host = std::make_shared<piga::Host>("config.yml", m_playerManager);

        m_host->init();

        m_playerManager->init();

        m_playerManager->getPlayer(0)->setName("Player 1");
        m_playerManager->getPlayer(0)->setActive(true);
        m_playerManager->getPlayer(1)->setName("Player 2");
        m_playerManager->getPlayer(1)->setActive(true);

        m_gameInput = std::make_shared<piga::GameInput>();
        
        m_host->setBackcallingGameInput(m_gameInput);

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

        m_textureManager = std::make_shared<PiH::TextureManager>(m_window->getSDLRenderer());
        m_fontManager = std::make_shared<PiH::FontManager>();
        
        m_hudContainer = new PiH::HudContainer(0);
        m_hudContainer->setBoundingBox(0, 0, m_window->getSize().x, m_window->getSize().y);

        m_directoryScanner = std::make_shared<DirectoryScanner>(m_host);
        m_directoryScanner->scanDirectory("Games");

        std::shared_ptr<PiH::ParticleSource> particles(new PiH::ParticleSource(m_hudContainer));
        particles->setDuration(0);
        particles->setGravity(-0.0001);
        particles->setSpawnsPerFrame(0.057);
        particles->setTargetCount((m_window->getSize().x * m_window->getSize().y) / 300);
        particles->setTexture(m_textureManager->getTexture("Data/Textures/GuiBackgroundEffects.png"));
        particles->setXSpeedRange(-0.025, 0.025);
        particles->setYSpeedRange(0.00005, 0.00007);
        particles->setRotationSpeedRange(0, 0);
        
        std::vector<PiH::IntRect> rects = {
            PiH::IntRect(0, 0, 128, 128),
            PiH::IntRect(133, 37, 80, 80),
            PiH::IntRect(0, 125, 400, 320),
            PiH::IntRect(0, 125, 400, 320)
        };
        
        particles->setTextureRectVector(rects);
        particles->setBoundingBox(m_hudContainer->getBoundingBox());
        particles->setXStartRange(0, m_window->getSize().x);
        particles->setYStartRange(-400, -401);
        m_hudContainer->addWidget(particles, "GuiBackgroundEffects");
        
        std::shared_ptr<GameChooser> chooser(new GameChooser(m_hudContainer));
        PiH::getGlobalConfig()->getFocusManager()->setFocused(chooser);
        chooser->setFont(m_fontManager->get("Data/Fonts/Roboto-Regular.ttf:22"));
        chooser->setTextureManager(m_textureManager);
        chooser->setDirectoryScanner(m_directoryScanner);
        
        PiH::HorizontalListLayout *horizontalLayout = new PiH::HorizontalListLayout();
        horizontalLayout->setSpacing(10);
        chooser->setLayouter(horizontalLayout);
        
        chooser->setBoundingBox(PiH::FloatRect(0, m_window->getSize().y / 4, m_window->getSize().x, m_window->getSize().y / 2));
        
        m_hudContainer->addWidget(chooser, "GameChooser");
        
        piga::GameEvent gameEvent;
        
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
            m_gameInput->update();
            m_host->update(frametime);
            while(m_gameInput->pollEvent(gameEvent))
            {
                if(!m_isSleeping)
                {
                    onGameEvent(gameEvent, frametime);
                }
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
        if(!m_isSleeping)
        {
            m_hudContainer->onUpdate(frametime);

            m_window->glClear();
            SDL_SetRenderDrawColor(m_window->getSDLRenderer(), 0, 0, 0, 0);
            SDL_RenderClear(m_window->getSDLRenderer());

            m_hudContainer->onRender(m_window->getSDLRenderer(), PiH::FloatRect(0, 0, m_window->getSize().x, m_window->getSize().y));
            SDL_RenderPresent(m_window->getSDLRenderer());
        }

        
        if(m_isSleeping && !m_host->gameIsRunning())
        {
            wakeupWindow();
        }
        else if(!m_isSleeping && m_host->gameIsRunning())
        {
            sleepWindow();
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
        m_hudContainer->setBoundingBox(0, 0, m_window->getSize().x, m_window->getSize().y);
        m_hudContainer->getWidget("GuiBackgroundEffects")->setBoundingBox(m_hudContainer->getBoundingBox());
        std::shared_ptr<PiH::ParticleSource> particles = std::static_pointer_cast<PiH::ParticleSource>(m_hudContainer->getWidget("GuiBackgroundEffects"));
        particles->setXStartRange(0, m_window->getSize().x);
        particles->setTargetCount(m_window->getSize().x * m_window->getSize().y / 300);
        m_hudContainer->getWidget("GameChooser")->setBoundingBox(PiH::FloatRect(0, m_window->getSize().y / 4, m_window->getSize().x, m_window->getSize().y / 2));
    }
    void App::setEnd(bool state)
    {
        m_end = state;
    }
    void App::onGameEvent(const piga::GameEvent &gameEvent, float frametime)
    {
        m_hudContainer->onEvent(PiH::Event(gameEvent, true));
        m_hudContainer->onEvent(PiH::Event(gameEvent, false));
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
