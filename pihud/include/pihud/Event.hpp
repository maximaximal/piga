#pragma once

#include <piga/GameEvent.hpp>

#include <pihud/Direction.hpp>
#include <pihud/InputEvent.hpp>
#include <pihud/FocusEvent.hpp>
#include <pihud/PigaEvent.hpp>

namespace PiH
{
    enum class EventType
    {
        NotSet,
        Direction,
        Input,
        Piga,
        Mouse,
        Focus,

        _COUNT
    };

    class Event
    {
        public:
            Event();
            Event(const InputEvent &inputEvent, int playerID = -1);
            Event(const FocusEvent &focusEvent, int playerID = -1);
            Event(const PigaEvent &pigaEvent, int playerID = -1);
            Event(const piga::GameEvent &gameEvent, bool focusEvent = false);
            virtual ~Event();

            EventType type;
            int playerID = -1;

            union
            {
                InputEvent input;
                FocusEvent focus;
                PigaEvent piga;
            };
    };
}
