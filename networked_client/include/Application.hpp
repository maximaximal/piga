#pragma once

#include <string>
#include <vector>
#include <memory>
#include <piga/SharedLibWrapper.hpp>
#include <piga/PlayerManager.hpp>

class Client;

class Application
{
    public:
        Application();
        ~Application();

        void parseConfig(const std::string &configFile);
        void init();
        void run();
        void exit();

        void handshakeCompleted();
    private:
        Client *m_client = nullptr;
        std::vector<std::unique_ptr<piga::SharedLibWrapper> > m_libs;
        std::shared_ptr<piga::PlayerManager> m_playerManager;
};
