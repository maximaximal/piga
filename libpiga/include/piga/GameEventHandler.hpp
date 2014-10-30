#ifndef LIBPIGA_PIGA_GAMEEVENTHANDLER_HPP_INCLUDED
#define LIBPIGA_PIGA_GAMEEVENTHANDLER_HPP_INCLUDED

#include <piga/GameEvent.hpp>

namespace piga
{
    /**
     * @brief The GameEventHandler class handles game events.
     */
    class GameEventHandler
    {
        public:
            void sendGameEvent(const GameEvent &gameEvent, float frametime);

        protected:
            virtual void onGameEvent(const GameEvent &gameEvent, float frametime);
    };
}

#endif
