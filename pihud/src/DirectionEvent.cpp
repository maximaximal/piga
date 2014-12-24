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
    DirectionEvent::DirectionEvent(piga::GameControl control, bool state)
    {
        switch(control)
        {
            case piga::UP:
                direction = UP;
                break;
            case piga::DOWN:
                direction = DOWN;
                break;
            case piga::LEFT:
                direction = LEFT;
                break;
            case piga::RIGHT:
                direction = RIGHT;
                break;
            default:
                //No direction specified
                break;
        }
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
