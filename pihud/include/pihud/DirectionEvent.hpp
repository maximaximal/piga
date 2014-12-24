#pragma once

#include <piga/GameControl.hpp>

namespace PiH
{
    enum Direction
    {
        DIRECTION_NOT_SET,
        UP,
        DOWN,
        LEFT,
        RIGHT,

        _COUNT
    };

    class DirectionEvent
    {
        public:
            DirectionEvent();
            DirectionEvent(Direction dir);
            DirectionEvent(piga::GameControl control, bool state);

            Direction direction;

            Direction getOpposite();
    };
}
