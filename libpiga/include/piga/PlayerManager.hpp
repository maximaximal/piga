#ifndef LIBPIGA_PIGA_PLAYERMANAGER_HPP_INCLUDED
#define LIBPIGA_PIGA_PLAYERMANAGER_HPP_INCLUDED

#include <memory>
#include <piga/Player.hpp>

#include <boost/interprocess/managed_shared_memory.hpp>

namespace piga
{
    class PlayerManager
    {
        public:
            PlayerManager();
            virtual ~PlayerManager();

            void init();

            Player* getPlayer(int playerID);

            int size();
        private:
            boost::interprocess::managed_shared_memory *m_players = nullptr;
            Player* m_mappedPlayers = nullptr;
            int m_mappedPlayersNum = 0;
    };
}

#endif
