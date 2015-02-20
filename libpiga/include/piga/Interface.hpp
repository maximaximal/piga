#ifndef LIBPIGA_PIGA_INTERFACE_HPP_INCLUDED
#define LIBPIGA_PIGA_INTERFACE_HPP_INCLUDED

#include <bitset>
#include <piga/PlayerInput.hpp>
#include <piga/GameInput.hpp>
#include <piga/GameEvent.hpp>

namespace piga
{
    /**
     * @brief The Interface class provides a simplified interface to the shared controls.
     * 
     * Example:
     * @includelineno interface.cpp
     */
    class Interface
    {
        public:
            /**
             * @brief Creates the interface.
             * 
             * @param selfhosted Marks if the interface should be @ref selfhosted_interface "selfhosted". 
             */
            Interface(bool selfhosted = false);
            /**
             * @brief Destructor. 
             */
            virtual ~Interface();

            /**
             * @brief Returns the player count of the host.
             * 
             * @return The player count. 
             */
            int getPlayerCount();
            /**
             * @brief Returns the player input of a specific player (only in selfhosted mode).
             * 
             * @param id The plyer id. 
             * @return const piga::PlayerInput&
             */
            const PlayerInput& getPlayerInput(int id);
            bool gameInputSet();
            /**
             * @brief Add a player input to the internal GameInput class. (Only in selfhosted mode)
             * 
             * @param playerInput The player input class to be added to the interface. 
             * @return The ID of the player in the GameInput class. 
             */
            int addPlayerInput(std::shared_ptr<PlayerInput> playerInput);

            /**
             * @brief Poll new events from the event queue. 
             * 
             * This works in both selfhosted and hosted mode. 
             * 
             * @param event A reference to a GameEvent class to be written to. 
             * @return True, as long as there was an event. This makes the function handy for while(pollEvent(event)) { } loops.
             */
            bool pollEvent(GameEvent &event);
            /**
             * @brief Checks, if the interface is selfhosted or not. 
             * 
             * @return bool True, if the interface is selfhosted, false otherwise. 
             */
            bool isSelfhosted();
            /**
             * @brief Updates the interface. This function is available in selfhosted and in hosted mode. 
             * 
             * This needs to be called every frame and updates the internal event queue. 
             */
            void update();
            void logToStatus(const std::string &message);
            
            /**
             * @brief Returns the remaining credits. Forwards the request to piga::Status::getCreditCount().
             * 
             * @return The remaining credits.
             */
            int getRemainingCredits();
            /**
             * @brief Set the remaining tickets to the specified count. Forwards to piga::Status::setRemainingCredits().
             * 
             * @param credits The remaining credits to be set.
             */
            void setRemainingCredits(int credits);
            /**
             * @brief Adds the specified amount of credits to the remaining credits. Forwards to piga::Status::addCredits().
             * 
             * @param amount The amount to be added to the remaining credits. Defaults to 1. 
             * @return The remaining tickets after this operation.
             */
            int addCredits(int amount = 1);
            /**
             * @brief Removes the specified amount of credits from the remaining tickets. Forwards to piga::Status::removeCredits().
             * 
             * @param amount The amount of credits to be removed. Defaults to 1. 
             * @return The remaining tickets after this operation.
             */
            int removeCredits(int amount = 1);
        private:
			std::deque<GameEvent> events;
            GameInput *externalGameInput = nullptr;
            bool m_selfhosted;
            std::vector<PlayerInputStruct> m_playerInputs;
    };
}

#endif
