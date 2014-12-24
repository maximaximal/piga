#include <pihud/InputEvent.hpp>

namespace PiH
{
    InputEvent::InputEvent()
    {
        text = "";
    }
    InputEvent::InputEvent(std::string input)
    {
        text = input;
    }
}
