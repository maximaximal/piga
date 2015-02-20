#include <piga/Events/GameInput.hpp>

namespace piga
{
    namespace event
    {
        GameInput::GameInput()
            : m_control(GameControl::ACTION)
        {
            setState(false);
        }
        GameInput::GameInput(GameControl control, bool state)
            : m_control(control)
        {
            if(state == false)
                m_value = 0;
            if(state == true)
                m_value = 100000;
        }
        GameInput::GameInput(GameControl control, int value)
            : m_control(control), m_value(value)
        {

        }
        GameInput::~GameInput()
        {

        }
        bool GameInput::state() const
        {
            if(m_value == 0)
                return false;
            else
                return true;
        }
        int GameInput::value() const
        {
            return m_value;
        }
        float GameInput::fValue() const
        {
            return (100000.0 / (float) value());
        }
        GameControl GameInput::control() const
        {
            return m_control;
        }
        void GameInput::setState(bool state)
        {
            if(state == false)
                m_value = 0;
            if(state == true)
                m_value = 100000;
        }
        void GameInput::setValue(int value)
        {
            m_value = value;
        }
        void GameInput::setFValue(float value)
        {
            m_value = value * 100000;
        }
        void GameInput::setControl(GameControl control)
        {
            m_control = control;
        }
        bool GameInput::operator==(const GameControl &rightControl) const
        {
            return m_control == rightControl;
        }
        GameInput &GameInput::operator=(const GameInput &otherInput)
        {
            m_value = otherInput.value();
            m_control = otherInput.control();
            return *this;
        }
        piga::event::GameInput::operator bool() const
        {
            return state();
        }
    }
}
