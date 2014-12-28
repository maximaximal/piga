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
    Event::Event(const FocusEvent &focusEvent)
    {
        type = EventType::Focus;
        focus = focusEvent;
    }
    Event::Event(const piga::GameEvent &gameEvent)
    {
        if(gameEvent.getControl() == piga::DOWN
                || gameEvent.getControl() == piga::LEFT
                || gameEvent.getControl() == piga::RIGHT
                || gameEvent.getControl() == piga::UP)
        {
            type = EventType::Direction;
            dir = DirectionEvent(gameEvent.getControl(), gameEvent);
        }
    }
    Event::~Event()
    {

    }
}
