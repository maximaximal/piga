#pragma once

#include <string>
#include <vector>
#include <memory>
#include <piga/SharedLibWrapper.hpp>
#include <piga/PlayerManager.hpp>
#include <piga/PlayerInput.hpp>

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
        bool m_handshakeCompleted = false;
        Client *m_client = nullptr;
        std::vector<std::unique_ptr<piga::SharedLibWrapper> > m_libs;
        std::vector<std::map<piga::GameControl, int> > m_inputs;
        std::shared_ptr<piga::PlayerManager> m_playerManager;
};
