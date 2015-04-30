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
        if(m_qmlApplicationEngine != nullptr)
            delete m_qmlApplicationEngine;
        if(m_guiApplication != nullptr)
            delete m_guiApplication;
    }
    void App::run(int argc, char* argv[])
    {
        LOG(INFO) << "Starting PiGaCo.";

        m_guiApplication = new QGuiApplication(argc, argv);
        m_qmlApplicationEngine = new QQmlApplicationEngine();
        m_qmlApplicationEngine->addImportPath("Data/forms/");
        m_qmlApplicationEngine->load(QUrl::fromLocalFile("Data/forms/MainMenu.qml"));

        QObject *topLevel = m_qmlApplicationEngine->rootObjects().value(0);
        m_qQuickWindow = qobject_cast<QQuickWindow*>(topLevel);

        m_qQuickWindow->showFullScreen();

        m_guiApplication->exec();

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

        m_directoryScanner = std::make_shared<DirectoryScanner>(m_host);
        m_directoryScanner->scanDirectory("Games");


        piga::GameEvent gameEvent;
        
        LOG(INFO) << "Starting the App-Loop.";

        while(!end())
        {
            frameTimePoint = std::chrono::high_resolution_clock::now();

            SDL_PumpEvents();
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
    void App::onUpdate(float frametime)
    {
        if(!m_isSleeping)
        {

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
    }
    void App::wakeupWindow()
    {
        m_isSleeping = false;
    }
    void App::setEnd(bool state)
    {
        m_end = state;
    }
    void App::onGameEvent(const piga::GameEvent &gameEvent, float frametime)
    {

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

    app->run(argv, argc);

    delete app;

    return 0;
}
