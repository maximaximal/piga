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
    bool PlayerInput::pollEvent(GameEvent &gameEvent)
    {
        if(m_gameEvents.size() > 0)
        {
            gameEvent = m_gameEvents.back();
            m_gameEvents.pop();
            return true;
        }
        return false;
    }
    void PlayerInput::setPlayerID(int playerID)
    {
        m_playerID = playerID;
    }
    void PlayerInput::update()
    {
		for(auto &method : m_inputMethods)
        {
            method.second->update();
            if(method.second->hasChanged())
            {
                GameEvent event(method.first, method.second->isActive(), m_playerID);
                pushGameEvent(event);
            }
        }
    }
    int PlayerInput::setInputMethod(InputMethod *method, GameControl control)
    {
        m_inputMethods[control] = method;
    }
    void PlayerInput::pushGameEvent(const GameEvent &gameEvent)
    {
        m_gameEvents.push(gameEvent);
    }
}
