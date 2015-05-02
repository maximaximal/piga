#pragma once

#include <string>
#include <enet/enet.h>
#include <NetworkedClient/PlayerManager.hpp>
#include <piga/PlayerInput.hpp>
#include <sigc++/sigc++.h>
#include <google/protobuf/message.h>

namespace NetworkedClient
{
    class Client
    {
        public:
            enum LoginResponse {
                LoginSuccessful,
                WrongCredentials,
                NoLoginPossible,
                NoMoreTries,
                UserIDNotExisting,
                UserIDAlreadyActive,
                Unknown,
                NotConnected,

                _COUNT
            };

            typedef sigc::signal<void> HandshakeCompletedSignal;
            typedef sigc::signal<void, LoginResponse> LoginResponseSignal;

            Client(std::shared_ptr<PlayerManager> playerManager);
            ~Client();

            void setServerAddress(const std::string &adress);
            void setServerPort(int port);

            const std::string& getServerAddress() const;
            int getServerPort() const;

            void connect();
            void update();
            bool disconnected();

            void login(const std::string &user, int userID = -1, const std::string &pass = "");

            HandshakeCompletedSignal& handshakeCompleted();
            LoginResponseSignal& loginResponse();

            void sendInputPacket(unsigned int playerID, piga::GameControl control, int input);
        private:
            void sendPacket(google::protobuf::Message &msg, const std::string &packetID, bool reliable);

            HandshakeCompletedSignal m_handshakeCompleted;
            LoginResponseSignal m_loginResponse;

            void receivePacket(ENetPacket *packet, ENetPeer *peer);
            ENetHost *m_client = nullptr;
            ENetPeer *m_serverPeer = nullptr;
            std::string m_serverAdress;
            int m_serverPort;
            bool m_connected = false;
            LoginResponse m_loginStatus = NotConnected;

            std::shared_ptr<PlayerManager> m_playerManager;
    };
}
