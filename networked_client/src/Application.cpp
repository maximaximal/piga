#include <NetworkedClient/Application.hpp>
#include <NetworkedClient/Client.hpp>
#include <yaml-cpp/yaml.h>

#define ELPP_NO_DEFAULT_LOG_FILE
#include <../../include/easylogging++.h>
INITIALIZE_EASYLOGGINGPP

namespace NetworkedClient
{
    Application::Application()
    {
        m_playerManager = std::make_shared<PlayerManager>();
        m_client = new Client(m_playerManager);
        m_client->handshakeCompleted().connect(sigc::mem_fun(this, &Application::handshakeCompleted));
    }
    Application::~Application()
    {
        delete m_client;
    }
    void Application::parseConfig(const std::string &configFile)
    {
        LOG(INFO) << "Parsing config file \"" << configFile << "\".";
        auto node = YAML::LoadAllFromFile(configFile);
        YAML::Node config;

        if(node.size() > 0)
        {
            config = node.front();
        }

        if(config)
        {
            if(config["ServerAddress"])
            {
                m_client->setServerAddress(config["ServerAddress"].as<std::string>());
            }
            else
            {
                LOG(WARNING) << "The \"ServerAddress\" property was not defined!";
            }
            if(config["ServerPort"])
            {
                m_client->setServerPort(config["ServerPort"].as<int>());
            }
            else
            {
                LOG(WARNING) << "The \"ServerPort\" property was not defined!";
            }
            if(config["Hosts"])
            {
                for(YAML::const_iterator it = config["Hosts"].begin(); it != config["Hosts"].end(); ++it)
                {
                    LOG(INFO) << "Loading \"" << (*it).as<std::string>() << "\".";
                    std::unique_ptr<piga::SharedLibWrapper> sharedLib(new piga::SharedLibWrapper((*it).as<std::string>()));
                    LOG(INFO) << "Loaded \"" << sharedLib->getName() << "\" by " << sharedLib->getAuthor() << ". It will be initialized when the connection to the server was successful.";
                    m_libs.push_back(std::move(sharedLib));
                }
            }
            else
            {
                LOG(WARNING) << "This client has no \"Hosts\" section in its config! No inputs will be processed.";
            }
        }
        else
        {
            LOG(WARNING) << "The config file was either not found or wrongly formatted!";
        }

    }
    void Application::init()
    {
        m_client->connect();
    }
    void Application::run()
    {
        int input = 0;

        while(!m_client->disconnected())
        {
            if(m_handshakeCompleted)
            {
                for(auto &lib : m_libs)
                {
                    for(auto &player : m_playerManager->getPlayers())
                    {
                        for(unsigned int i = 0; i < piga::GameControl::_COUNT; ++i)
                        {
                            input = lib->getButtonState(player.first, static_cast<piga::GameControl>(i));

                            if(m_inputs[player.first][static_cast<piga::GameControl>(i)] != input)
                            {
    LOG(INFO) << "INPUT DETECTED!";
                                m_inputs[player.first][static_cast<piga::GameControl>(i)] = input;
                            m_client->sendInputPacket(player.first, static_cast<piga::GameControl>(i), input);
                            }
                        }
                    }
                }
            }
            m_client->update();
        }
    }
    void Application::exit()
    {
        m_libs.clear();
        m_handshakeCompleted = false;
    }
    void Application::handshakeCompleted()
    {
        m_inputs.clear();

        m_handshakeCompleted = true;
        for(auto &lib : m_libs)
        {
            m_inputs.resize(m_playerManager->size());
            for(unsigned int i = 0; i < m_playerManager->size(); ++i)
            {
                std::map<piga::GameControl, int> inputsMap;

                for(auto &input : inputsMap)
                {
                    input.second = 0;
                }

                m_inputs[i] = inputsMap;
            }

            lib->init(m_playerManager->size());
        }
    }
}

int main(int argv, char* argc[])
{
    using namespace NetworkedClient;

    START_EASYLOGGINGPP(argv, argc);

    el::Configurations conf;

    conf.setToDefault();
    conf.setGlobally(el::ConfigurationType::ToFile, "false");

    el::Loggers::reconfigureAllLoggers(conf);

    LOG(INFO) << "Starting networked piga client.";

    Application *app = new Application();

    bool end = false;

    while(!end)
    {
        app->parseConfig("config.yml");
        app->init();
        app->run();
        app->exit();
    }

    delete app;

    return 0;
}
