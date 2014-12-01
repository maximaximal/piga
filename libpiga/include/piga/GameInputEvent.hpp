#ifndef LIBPIGA_PIGA_GAMEINPUTEVENT_HPP_INCLUDED
#define LIBPIGA_PIGA_GAMEINPUTEVENT_HPP_INCLUDED

#include <piga/GameControl.hpp>

namespace piga
{
    /**
     * @brief The GameInputEvent class holds game input events.
     *
     * This event is only responsoble for boolean events!
     */
    class GameInputEvent
    {
        public:
            GameInputEvent(GameControl control, bool state, int frame = 0);
            virtual ~GameInputEvent();
            GameControl control;
            bool state = false;
            int frame;
    };
}

#endif
