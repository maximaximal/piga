#include <pihud/DirectionEvent.hpp>

namespace PiH
{
    DirectionEvent::DirectionEvent()
    {
		direction = DIRECTION_NOT_SET;
    }
    DirectionEvent::DirectionEvent(Direction dir)
    {
        direction = dir;
    }
    Direction DirectionEvent::getOpposite()
    {
        switch(direction)
        {
            case UP:
                return DOWN;
            case DOWN:
                return UP;
            case LEFT:
                return RIGHT;
            case RIGHT:
                return LEFT;
            default:
                return DIRECTION_NOT_SET;
        }
    }
}
