#include <pihud/Event.hpp>

namespace PiH
{
    Event::Event()
    {
		type = EventType::NotSet;
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
    Event::Event(const piga::GameEvent &gameEvent, bool focusEvent)
    {
        if(gameEvent.type() == piga::GameEvent::GameInput && !focusEvent)
        {
            PigaEvent pigaEvent(gameEvent.gameInput.control(), gameEvent.gameInput.state());
            type = EventType::Piga;
            piga = pigaEvent;
        }
        else if(gameEvent.type() == piga::GameEvent::GameInput)
        {
            if(gameEvent.gameInput.control() == piga::DOWN
                    || gameEvent.gameInput.control() == piga::LEFT
                    || gameEvent.gameInput.control() == piga::RIGHT
                    || gameEvent.gameInput.control() == piga::UP
                    && focusEvent)
            {
                type = EventType::Focus;
                focus = FocusEvent(gameEvent);
            }
        }
    }
    Event::~Event()
    {

    }
}
