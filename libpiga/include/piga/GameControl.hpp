#ifndef LIBPIGA_PIGA_GAMECONTROL_HPP_INCLUDED
#define LIBPIGA_PIGA_GAMECONTROL_HPP_INCLUDED

namespace piga 
{
    /**
     * @brief The GameControl enum is the foundation of the input system of piga.
     *
     * This enum defines all inputs possible through the connected buttons. For in-depth
     * explanation of the individual buttons, see @ref event_system ["event system"].
     */
    enum GameControl 
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        
        ACTION,

        BUTTON1,
        BUTTON2,
        BUTTON3,
        BUTTON4,
        BUTTON5,
        BUTTON6,
        
        _COUNT
    };

    /**
     * @brief Converts a GameControl enum value to a host-define integer.
     *
     * The host defined integers are found in the @ref ../../hosts/host.h ["host header file"].
     *
     * @param control
     * @return
     */
    int GameControlToHostDefine(GameControl control);
    GameControl HostDefineToGameControl(int define);
}

#endif
