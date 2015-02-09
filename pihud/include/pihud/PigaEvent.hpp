#pragma once

#include <piga/GameControl.hpp>

namespace PiH
{
    /**
     * @brief Holds a piga game event.
     * 
     * The GameControl enum from piga is represented in pihud through this. This does
     * not include any other piga events though.
     */
    class PigaEvent
    {
        public:
            PigaEvent(piga::GameControl control = piga::ACTION, bool state = true);
            virtual ~PigaEvent();
            
            piga::GameControl control;
            bool state;
    };
}