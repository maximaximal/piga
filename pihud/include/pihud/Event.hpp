#pragma once

#include <piga/GameEvent.hpp>

#include <pihud/DirectionEvent.hpp>
#include <pihud/InputEvent.hpp>

namespace PiH
{
    enum class EventType
    {
        NotSet,
        Direction,
        Input,
        Mouse,

        _COUNT
    };

    class Event
    {
        public:
            Event();
            Event(const DirectionEvent &dirEvent);
            Event(const InputEvent &inputEvent);
            Event(const piga::GameEvent &gameEvent);
            virtual ~Event();

			EventType type;

            union
            {
				DirectionEvent dir;
                InputEvent input;
            };
    };
}
