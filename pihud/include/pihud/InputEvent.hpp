#pragma once

#include <string>

namespace PiH
{
    class InputEvent
    {
        public:
            InputEvent();
            InputEvent(std::string input);

            std::string text;
    };
}
