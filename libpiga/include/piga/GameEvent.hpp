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
            GameEvent(GameControl control, bool state);
            virtual ~GameEvent();

            bool isActive() const;
            GameControl getControl() const;

            bool operator==(const GameControl &rightControl) const;
            operator bool() const;
        private:
            const GameControl m_control;
            const bool m_state;
    };
}

#endif
