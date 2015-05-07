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
            void setServerName(const std::string &name);
            void setServerPort(int port);
            void setLoginStatus(LoginResponse response);

            const std::string& getServerAddress() const;
            const std::string& getServerName() const;
            int getServerPort() const;
            LoginResponse getLoginStatus() const;
            std::shared_ptr<PlayerManager> getPlayerManager() const;

            void connect();
            bool update();
            bool disconnected();

            void login(const std::string &user, int userID = -1, const std::string &pass = "");

            HandshakeCompletedSignal& handshakeCompleted();
            LoginResponseSignal& loginResponse();

            void sendInputPacket(unsigned int playerID, piga::GameControl control, int input);
        private:
            void sendPacket(google::protobuf::Message &msg, const std::string &packetID, bool reliable);

            HandshakeCompletedSignal m_handshakeCompleted;
            LoginResponseSignal m_loginResponse;

            bool receivePacket(ENetPacket *packet, ENetPeer *peer);
            ENetHost *m_client = nullptr;
            ENetPeer *m_serverPeer = nullptr;
            std::string m_serverAdress;
            std::string m_serverName;
            int m_serverPort;
            bool m_connected = false;
            LoginResponse m_loginStatus = NotConnected;

            std::shared_ptr<PlayerManager> m_playerManager;
    };
}
