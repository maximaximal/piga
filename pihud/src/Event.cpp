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
    Event::Event(const PigaEvent &pigaEvent)
    {
        type = EventType::Piga;
        piga = pigaEvent;
    }
    Event::Event(const piga::GameEvent &gameEvent)
    {
        if(gameEvent.type() == piga::GameEvent::GameInput)
        {
            PigaEvent pigaEvent(gameEvent.gameInput.control(), gameEvent.gameInput.state());
            type = EventType::Piga;
            piga = pigaEvent;
        }
        if(gameEvent.gameInput.control() == piga::DOWN
                || gameEvent.gameInput.control() == piga::LEFT
                || gameEvent.gameInput.control() == piga::RIGHT
                || gameEvent.gameInput.control() == piga::UP)
        {
            type = EventType::Direction;
            dir = DirectionEvent(gameEvent.gameInput.control(), gameEvent.gameInput.state());
        }
    }
    Event::~Event()
    {

    }
}
