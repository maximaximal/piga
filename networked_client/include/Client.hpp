#pragma once

#include <string>
#include <enet/enet.h>
#include <piga/PlayerManager.hpp>
#include <sigc++/sigc++.h>

class Client
{
    public:
        typedef sigc::signal<void> HandshakeCompletedSignal;
        Client(std::shared_ptr<piga::PlayerManager> playerManager);
        ~Client();

        void setServerAdress(const std::string &adress);
        void setServerPort(int port);

        const std::string& getServerAdress();
        int getServerPort();

        void connect();
        void update();
        bool disconnected();

        HandshakeCompletedSignal& handshakeCompleted();
    private:
        HandshakeCompletedSignal m_handshakeCompleted;
        void receivePacket(ENetPacket *packet, ENetPeer *peer);
        ENetHost *m_client = nullptr;
        ENetPeer *m_serverPeer = nullptr;
        std::string m_serverAdress;
        int m_serverPort;
        bool m_connected = false;

        std::shared_ptr<piga::PlayerManager> m_playerManager;
};
