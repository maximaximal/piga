#include <pigaco/App.hpp>

#include <easylogging++.h>

_INITIALIZE_EASYLOGGINGPP

namespace pigaco
{
    App::App()
    {
        LOG(INFO) << "Starting PiGaCo app.";
		m_host = std::make_shared<piga::Host>();
        m_host->init();
    }
    App::~App()
    {

    }
}

int main()
{
    pigaco::App *app = new pigaco::App();

    delete app;

    return 0;
}
