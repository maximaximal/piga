#ifndef LIBPIGA_PIGA_GAMEEVENTHANDLER_HPP_INCLUDED
#define LIBPIGA_PIGA_GAMEEVENTHANDLER_HPP_INCLUDED

#include <sigc++/signal.h>
#include <piga/GameEvent.hpp>

namespace piga
{
    /**
     * @brief The GameEventHandler class handles game events.
     */
    class GameEventHandler
    {
        public:
            typedef sigc::signal<void, const GameEvent&, float> GameEventSignal;

            void sendGameEvent(const GameEvent &gameEvent, float frametime);

            /**
             * @brief Gets the game event signal. The signal is fired when an event occurs.
             * @return A reference to the game event signal of this handler.
             */
            GameEventSignal& getGameEventSignal();
        protected:
            virtual void onGameEvent(const GameEvent &gameEvent, float frametime);
            GameEventSignal m_signal;
    };
}

#endif
