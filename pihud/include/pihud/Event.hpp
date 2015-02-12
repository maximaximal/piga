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
            Event(const InputEvent &inputEvent);
            Event(const FocusEvent &focusEvent);
            Event(const PigaEvent &pigaEvent);
            Event(const piga::GameEvent &gameEvent, bool focusEvent = false);
            virtual ~Event();

            EventType type;

            union
            {
                InputEvent input;
                FocusEvent focus;
                PigaEvent piga;
            };
    };
}
