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

            void init();

            void applyFromGameInput(GameInput *gameInput);

            void setInput(unsigned int playerID, GameControl control, bool state);

            void setCurrentGameHost(std::shared_ptr<GameHost> gameHost);
            void setPlayerManager(std::shared_ptr<PlayerManager> playerManager);

            bool gameIsRunning();

            void update(float frametime);

            static const char* getInputSharedMemoryName();
            static const char* getStatusSharedMemoryName();
        protected:
            void createSharedMemory();
            void deleteSharedMemory();
        private:
            //Settings of the physical appearence of the console.
            unsigned int m_playerCount = 2;
            unsigned int m_buttonCount = 11;
            void sendHandshakePacket(ENetPeer *peer);
            std::shared_ptr<GameHost> m_currentGameHost;
            std::shared_ptr<PlayerManager> m_playerManager;
            std::vector<std::shared_ptr<SharedLibWrapper> > m_sharedLibs;
            std::string m_configFile;
            std::string m_name = "Unnamed Host";
            bool m_useSharedMemory = true;
            ENetHost *m_enetHost = nullptr;
            std::map<int, ENetPeer*> m_enetPeers;
    };
}

#endif
