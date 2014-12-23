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

        LOG(INFO) << "Starting the App-Loop.";
        while(!end())
        {
            frameTimePoint = std::chrono::high_resolution_clock::now();

            update(frametime);

            LOG(INFO) << "FRAMETIME:" << frametime << " - Desired: " << desiredFrametime.count();

            frametime = std::chrono::duration_cast<std::chrono::milliseconds>(frameTimePoint - frameTimePointPast).count();

            if(frametime < desiredFrametime.count())
                std::this_thread::sleep_for(desiredFrametime - std::chrono::duration_cast<std::chrono::milliseconds>(frameTimePoint - frameTimePointPast));

            frameTimePointPast = frameTimePoint;
        }
    }
    void App::update(float frametime)
    {

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
