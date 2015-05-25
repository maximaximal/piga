#ifndef LIBPIGA_PIGA_PLAYERMANAGER_HPP_INCLUDED
#define LIBPIGA_PIGA_PLAYERMANAGER_HPP_INCLUDED

#include <memory>
#include <piga/Player.hpp>

#include <boost/interprocess/managed_shared_memory.hpp>

namespace piga
{
    /**
     * @brief The PlayerManager class manages access to the players on the current piga console.
     *
     * Players in the manager may be saved in shared memory (if the piga::Interface is not selfhosted) or
     * locally in the manager.
     */
    class PlayerManager
    {
        public:
            /**
             * @brief Construct the player manager.
             * @param sharedMemory Defines if shared memory should be used. If true, the manager
             * will try to access the players from shared memory. If false, the
             * manager will create the players itself.
             *
             * @param playerNum The maximum number of players.
             */
            PlayerManager(bool sharedMemory = true, int playerNum = 16);
            /**
             * @brief Destructor of the player manager.
             */
            virtual ~PlayerManager();

            /**
             * @brief Initiates the player manager.
             *
             * When this function gets called, the manager tries to access the shared memory
             * or to create the internal player array. The host-application (pigaco) has to
             * be running before this function is called, or else shared memory will not work!
             */
            void init();

            /**
             * @brief Returns the specified player from the internal/shared player array.
             * @param playerID The ID of the player.
             * @return A raw pointer to the player. Do not delete this pointer, the player is owned by the manager!
             */
            Player *getPlayer(int playerID);

            /**
             * @brief Returns the maximum number of players.
             * @return The maximum number of players.
             */
            int size();

            /**
             * @brief Resets all the edited flags of the players.
             *
             * When this function is run, it checks if a player has been edited. If
             * a player changed, the internal m_playerEdited flag is set and can be checked through the
             * playerEdited() function.
             *
             * This function should only be used by the host at the end of the update loop!
             */
            void resetEdited();

            /**
             * @brief Returns the internal m_playerEdited flag.
             * @return True if a player has been edited, false otherwise.
             */
            bool playerEdited();

            /**
             * @brief setPlayerEdited Sets the internal m_playerEdited flag to the specified state.
             * @param state The state the internal m_playerEdited flag should be set to.
             */
            void setPlayerEdited(bool state);
        private:
            boost::interprocess::managed_shared_memory *m_players = nullptr;
            Player* m_mappedPlayers = nullptr;
            int m_mappedPlayersNum = 0;
            bool m_sharedMemory = true;
            bool m_playerEdited = false;
    };
}

#endif
