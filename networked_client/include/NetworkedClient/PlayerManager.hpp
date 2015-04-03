#pragma once

#include <memory>
#include <map>
#include <exception>
#include <piga/Player.hpp>

namespace NetworkedClient
{
    /**
     * @brief The PlayerManager class in the networked client serves as a dynamic cache for player data.
     */
    class PlayerManager
    {
        public:
            typedef std::map<unsigned int, std::shared_ptr<piga::Player> > PlayerMap;

            PlayerManager();
            virtual ~PlayerManager();

            void set(std::shared_ptr<piga::Player> &player, unsigned int id);
            std::shared_ptr<piga::Player> get(unsigned int id);
            void clear();
            PlayerMap& getPlayers();
            unsigned int size();

            class PlayerNotFound : std::exception
            {
                public:
                    PlayerNotFound(const char *message = "Player not found!");
                    virtual ~PlayerNotFound();

                    virtual const char* what() const noexcept;
                private:
                    const char* m_msg;
            };

        private:
            PlayerMap m_players;
    };
}
