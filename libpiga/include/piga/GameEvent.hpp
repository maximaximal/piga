#ifndef LIBPIGA_PIGA_GAMEEVENT_HPP_INCLUDED
#define LIBPIGA_PIGA_GAMEEVENT_HPP_INCLUDED

#include <piga/GameControl.hpp>

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
            GameEvent(GameControl control, bool state, int playerID);
            GameEvent(const GameEvent &gameEvent);
            virtual ~GameEvent();

            bool isActive() const;
            GameControl getControl() const;
            int getPlayerID() const;

            bool operator==(const GameControl &rightControl) const;
            bool operator==(int playerID) const;
            void operator=(const GameEvent &right);
            operator bool() const;
        private:
            GameControl m_control;
            bool m_state;
            int m_playerID;
    };
}

#endif
