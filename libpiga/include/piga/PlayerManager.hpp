#ifndef LIBPIGA_PIGA_PLAYERMANAGER_HPP_INCLUDED
#define LIBPIGA_PIGA_PLAYERMANAGER_HPP_INCLUDED

#include <memory>
#include <piga/Player.hpp>

namespace piga
{
    class PlayerManager
    {
        public:
            PlayerManager();
            virtual ~PlayerManager();

            std::shared_ptr<Player> get(unsigned int playerID);

            void set(std::shared_ptr<Player> player, unsigned int id);
        private:
            std::map<unsigned int, std::shared_ptr<Player> > m_players;
    };
}

#endif
