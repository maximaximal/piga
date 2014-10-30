#include <piga/GameEvent.hpp>

namespace piga
{
    GameEvent::GameEvent(GameControl control, bool state)
        : m_control(control), m_state(state)
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
    bool GameEvent::operator==(const GameControl &rightControl) const
    {
        if(getControl() == rightControl)
            return true;
        return false;
    }
    piga::GameEvent::operator bool() const
    {
        return this->isActive();
    }
}
