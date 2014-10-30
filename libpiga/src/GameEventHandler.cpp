#include <piga/GameEventHandler.hpp>

namespace piga
{
    void GameEventHandler::sendGameEvent(const GameEvent &gameEvent, float frametime)
    {
        onGameEvent(gameEvent, frametime);
    }
    void GameEventHandler::onGameEvent(const GameEvent &gameEvent, float frametime)
    {
        //Implemented by the derived class.
    }
}
