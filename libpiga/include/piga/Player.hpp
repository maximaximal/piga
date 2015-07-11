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
     * because the API might change.
     */
    class Player
    {
        public:
            Player(const char *username = "Unknown", bool active = false, int playerID = 0);

            void setName(const char *name);
            void setActive(bool active = true);
            void setPlayerID(int id);

            const char* getName();
            int getPlayerID();

            bool isActive();
            void setEdited(bool state);
            bool edited();
        private:
            char m_name[255];
            bool m_authorized = false;
            int m_playerID = 0;
            bool m_active = false;
            bool m_edited = false;

            boost::shared_mutex m_nameMutex;
            boost::shared_mutex m_authorizedMutex;
            boost::shared_mutex m_activeMutex;
            boost::shared_mutex m_editedMutex;
    };
}

#endif
