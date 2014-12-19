#ifndef LIBPIGA_PIGA_PLAYER_HPP_INCLUDED
#define LIBPIGA_PIGA_PLAYER_HPP_INCLUDED

#include <string>

#include <boost/thread/shared_mutex.hpp>

namespace piga
{
    /**
     * @brief The Player class handles players in the piga environment.
     *
     * This class is threadsafe, so you do not have to worry about threads when using this. Names
     * and other stats can change without actions on your side, so the best method to display player
     * stats is to query this instance every frame.
     *
     * This class can be derived from to use it for your own needs. This is not recommended though,
     * because the API may change.
     */
    class Player
    {
        public:
            Player(int playerID, const std::string &username = "Unknown");

            bool isAuthorized();

            void authorize(const std::string &password);

			void setName(const std::string &name);

            const std::string& getName();
            int getPlayerID();
        private:
            std::string m_name = "Unknown";
            bool m_authorized = false;
            int m_playerID = 0;

            boost::shared_mutex m_nameMutex;
            boost::shared_mutex m_authorizedMutex;
    };
}

#endif
