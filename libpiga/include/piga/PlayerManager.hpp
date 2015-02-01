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

            void clear();

            std::shared_ptr<Player> get(unsigned int playerID);

            void set(std::shared_ptr<Player> player, unsigned int id);

            std::size_t size();

            std::map<unsigned int, std::shared_ptr<Player> >& getPlayers();
        private:
            std::map<unsigned int, std::shared_ptr<Player> > m_players;
    };
}

#endif
