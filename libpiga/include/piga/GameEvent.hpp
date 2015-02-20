#ifndef LIBPIGA_PIGA_GAMEEVENT_HPP_INCLUDED
#define LIBPIGA_PIGA_GAMEEVENT_HPP_INCLUDED

#include <piga/GameControl.hpp>

#include <piga/Events/GameInput.hpp>
#include <piga/Events/TextInput.hpp>

namespace piga
{
    /**
     * @brief Provides an integrated interface to game events.
     *
     * This class can be used to integrate piga better into your application.
     */
    class GameEvent
    {
        public:
            /**
             * @brief Type of the event. 
             * 
             * This enum defines the existing event types. 
             */
            enum GameEventType {
                GameInput,
                TextInput,
                Undefined,

                _COUNT
            };


            /**
             * @brief Constructs a GameEvent using another GameEvent instance. 
             * 
             * @param gameEvent The other event to copy from.
             */
            GameEvent(const GameEvent &gameEvent);
            /**
             * @brief Constructs a GameEvent with only the player id as a parameter.
             * 
             * @param playerID The player id of the player who was the origin of the event.
             */
            GameEvent(int playerID = 0);
            /**
             * @brief Constructs a GameEvent using a GameInput instance.
             * 
             * @param playerID The player id of the player who was the origin of the event.
             * @param gameInput The GameInput instance to copy from. 
             */
            GameEvent(int playerID, const event::GameInput &gameInput);
            /**
             * @brief Constructs a GameEvent using a TextInput instance.  
             * 
             * @param playerID The player id of the player who was the origin of the event.
             * @param textInput The TextInput instance to copy from.
             */
            GameEvent(int playerID, const event::TextInput &textInput);
            /**
             * @brief Destructs the GameEvent instance. 
             */
            virtual ~GameEvent();

            /**
             * @brief Sets the player id of this GameEvent instance. 
             * 
             * @param playerID The player id to be set as an origin of this GameEvent. 
             */
            void setPlayerID(int playerID);
            /**
             * @brief Returns the id of the player who created this GameEvent.
             * 
             * @return The ID of the player.
             */
            int playerID() const;
            /**
             * @brief Returns the GameEventType of this event. 
             * 
             * @return The GameEventType of this GameEvent.
             */
            GameEventType type() const;

            /**
             * @brief Holds the event classes. 
             */
            union
            {
                event::GameInput gameInput;
                event::TextInput textInput;
            };

            GameEvent& operator=(const GameEvent &otherEvent);
            void operator=(const event::GameInput &gameInput);
            void operator=(const event::TextInput &textInput);
        private:
            int m_playerID;
            GameEventType m_type;
    };
}

#endif
