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
            enum GameEventType {
                GameInput,
                TextInput,
                Undefined,

                _COUNT
            };


            GameEvent(const GameEvent &gameEvent);
            GameEvent(int playerID = 0);
            GameEvent(int playerID, const event::GameInput &gameInput);
            GameEvent(int playerID, const event::TextInput &textInput);
            virtual ~GameEvent();

            void setPlayerID(int playerID);
            int playerID() const;
            GameEventType type() const;

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
