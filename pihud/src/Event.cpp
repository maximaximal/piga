#include <pihud/Event.hpp>

namespace PiH
{
    Event::Event()
    {
		type = EventType::NotSet;
    }
    Event::Event(const InputEvent &inputEvent, int playerID)
    {
        type = EventType::Input;
        input = inputEvent;
        this->playerID = playerID;
    }
    Event::Event(const FocusEvent &focusEvent, int playerID)
    {
        type = EventType::Focus;
        focus = focusEvent;
        this->playerID = playerID;
    }
    Event::Event(const PigaEvent &pigaEvent, int playerID)
    {
        type = EventType::Piga;
        piga = pigaEvent;
        this->playerID = playerID;
    }
    Event::Event(const piga::GameEvent &gameEvent, bool focusEvent)
    {
        playerID = gameEvent.playerID();
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
