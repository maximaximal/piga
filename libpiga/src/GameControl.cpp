#include <piga/GameControl.hpp>

namespace piga
{
    int GameControlToHostDefine(piga::GameControl control)
    {
        return static_cast<int>(control);
    }
    GameControl HostDefineToGameControl(int define)
    {
        return static_cast<GameControl>(define);
    }
}
