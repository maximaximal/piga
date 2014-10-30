#include <piga/GameEventHandler.hpp>

namespace piga
{
    void GameEventHandler::sendGameEvent(const GameEvent &gameEvent)
    {
        onGameEvent(gameEvent);
    }
    void GameEventHandler::onGameEvent(const GameEvent &gameEvent)
    {
        //Implemented by the derived class.
    }
}
