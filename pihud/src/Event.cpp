#include <pihud/Event.hpp>

namespace PiH
{
    Event::Event()
    {
		type = EventType::NotSet;
    }
    Event::Event(const DirectionEvent &dirEvent)
    {
        type = EventType::Direction;
        dir = dirEvent;
    }
    Event::Event(const InputEvent &inputEvent)
    {
        type = EventType::Input;
        input = inputEvent;
    }
    Event::~Event()
    {

    }
}
