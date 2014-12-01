#include <piga/GameInputEvent.hpp>

namespace piga
{
    GameInputEvent::GameInputEvent(GameControl control, bool state, int frame)
    {
        this->control = control;
        this->state = state;
        this->frame = frame;
    }
    GameInputEvent::~GameInputEvent()
    {

    }
}
