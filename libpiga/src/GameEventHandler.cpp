#include <piga/GameEventHandler.hpp>

namespace piga
{
    void GameEventHandler::sendGameEvent(const GameEvent &gameEvent, float frametime)
    {
        onGameEvent(gameEvent, frametime);
        m_signal(gameEvent, frametime);
    }
    GameEventHandler::GameEventSignal &GameEventHandler::getGameEventSignal()
    {
        return m_signal;
    }
    void GameEventHandler::onGameEvent(const GameEvent &gameEvent, float frametime)
    {
        //Implemented by the derived class.
    }
}
