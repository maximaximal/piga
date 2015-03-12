#ifndef LIBPIGA_PIGA_HOST_HPP_INCLUDED
#define LIBPIGA_PIGA_HOST_HPP_INCLUDED

#include <piga/GameInput.hpp>
#include <piga/SharedLibWrapper.hpp>
#include <piga/PlayerManager.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <vector>
#include <enet/enet.h>

namespace piga
{
    class GameHost;

    /**
     * @brief The Host class hosts the controls for all applications running on piga.
     *
     * This class has to be used by the master application which controls all other apps!
     */
    class Host
    {
        public:
            Host(const std::string &configFile, std::shared_ptr<PlayerManager> playerManager);
            virtual ~Host();

            void init(int playerCount = 16);

            void applyFromGameInput(GameInput *gameInput);

            void setInput(unsigned int playerID, GameControl control, bool state);

            void setCurrentGameHost(GameHost *gameHost);
            void setPlayerManager(std::shared_ptr<PlayerManager> playerManager);

            bool gameIsRunning(bool fsCheck = false);

            void update(float frametime);
            void setBackcallingGameInput(std::shared_ptr<GameInput> gameInput);

            static const char* getInputSharedMemoryName();
            static const char* getStatusSharedMemoryName();
            static const char* getPlayersSharedMemoryName();
        protected:
            void createSharedMemory(int playerCount);
            void deleteSharedMemory();
        private:
            //Settings of the physical appearence of the console.
            unsigned int m_playerCount = 2;
            unsigned int m_buttonCount = 11;
            void sendHandshakePacket(ENetPeer *peer);
            void receivePacket(ENetPacket *packet, ENetPeer *peer);
            GameHost *m_currentGameHost = nullptr;
            std::shared_ptr<PlayerManager> m_playerManager;
            std::shared_ptr<GameInput> m_backcallingGameInput;
            std::vector<std::shared_ptr<SharedLibWrapper> > m_sharedLibs;
            std::string m_configFile;
            std::string m_name = "Unnamed Host";
            bool m_useSharedMemory = true;
            ENetHost *m_enetHost = nullptr;
            std::map<int, ENetPeer*> m_enetPeers;
            float m_isRunningTimer = 0;
    };
}

#endif
