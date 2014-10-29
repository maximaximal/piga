#include <piga/PlayerInput.hpp>

namespace piga
{
    PlayerInput::PlayerInput()
    {
		for(unsigned int i = 0; i < GameControl::_COUNT; ++i)
        {
            GameControl control = static_cast<GameControl>(i);

            m_inputMethods[control] = nullptr;
        }
    }
    PlayerInput::~PlayerInput()
    {
        for(auto &method : m_inputMethods)
        {
            delete method.second;
            method.second = nullptr;
        }
        m_inputMethods.clear();
    }

    bool PlayerInput::getInput(GameControl control) const
    {
        const InputMethod *method = m_inputMethods.find(control)->second;
        if(method != nullptr)
        {
            return method->isActive();
        }
        return false;
    }
    void PlayerInput::update()
    {
		for(auto &method : m_inputMethods)
        {
            method.second->update();
        }
    }
    int PlayerInput::setInputMethod(InputMethod *method, GameControl control)
    {
		m_inputMethods[control] = method;
    }
}
