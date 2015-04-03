#pragma once

#include <string>
#include <enet/enet.h>
#include <NetworkedClient/PlayerManager.hpp>
#include <piga/PlayerInput.hpp>
#include <sigc++/sigc++.h>

namespace NetworkedClient
{
    class Client
    {
        public:
            typedef sigc::signal<void> HandshakeCompletedSignal;
            Client(std::shared_ptr<PlayerManager> playerManager);
            ~Client();

            void setServerAddress(const std::string &adress);
            void setServerPort(int port);

            const std::string& getServerAddress();
            int getServerPort();

            void connect();
            void update();
            bool disconnected();

            HandshakeCompletedSignal& handshakeCompleted();

            void sendInputPacket(unsigned int playerID, piga::GameControl control, int input);
        private:
            HandshakeCompletedSignal m_handshakeCompleted;
            void receivePacket(ENetPacket *packet, ENetPeer *peer);
            ENetHost *m_client = nullptr;
            ENetPeer *m_serverPeer = nullptr;
            std::string m_serverAdress;
            int m_serverPort;
            bool m_connected = false;

            std::shared_ptr<PlayerManager> m_playerManager;
    };
}
