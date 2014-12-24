#pragma once

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

            Direction direction;

            Direction getOpposite();
    };
}
