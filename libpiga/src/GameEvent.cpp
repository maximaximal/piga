#include <piga/GameEvent.hpp>

namespace piga
{
    GameEvent::GameEvent(GameControl control, bool state, int playerID)
        : m_control(control), m_state(state), m_playerID(playerID)
    {

    }
    GameEvent::GameEvent(const GameEvent &gameEvent)
        : m_control(gameEvent.getControl()), m_state(gameEvent.isActive()), m_playerID(gameEvent.getPlayerID())
    {

    }
    GameEvent::~GameEvent()
    {

    }
    bool GameEvent::isActive() const
    {
        return m_state;
    }
    GameControl GameEvent::getControl() const
    {
        return m_control;
    }
    int GameEvent::getPlayerID() const
    {
        return m_playerID;
    }
    bool GameEvent::operator==(const GameControl &rightControl) const
    {
        if(getControl() == rightControl)
            return true;
        return false;
    }
    bool GameEvent::operator==(int playerID) const
    {
        if(getPlayerID() == playerID)
        {
            return true;
        }
        return false;
    }
    void GameEvent::operator=(const GameEvent &right)
    {
        m_state = right.isActive();
        m_control = right.getControl();
        m_playerID = right.getPlayerID();
    }
    piga::GameEvent::operator bool() const
    {
        return this->isActive();
    }
}
