#include <pihud/PigaEvent.hpp>

namespace PiH
{
    PigaEvent::PigaEvent(piga::GameControl control, bool state)
        : control(control), state(state)
    {
        
    }
    PigaEvent::~PigaEvent()
    {

    }
}