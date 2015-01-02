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
            m_gameEvents.pop_back();
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
            if(method.second->hasChanged())
            {
                GameEvent event(method.first, method.second->isActive(), m_playerID);
                pushGameEvent(event);
            }
            method.second->update();
        }
    }
    int PlayerInput::setInputMethod(InputMethod *method, GameControl control)
    {
        m_inputMethods[control] = method;
    }
    void PlayerInput::pushGameEvent(const GameEvent &gameEvent)
    {
        m_gameEvents.push_front(gameEvent);
    }

    void PlayerInputStruct::fromGameEvent(GameEvent &e)
    {
        fromGameEvent(e.getControl(), (bool) e);
    }
    void PlayerInputStruct::fromGameEvent(const GameControl &control, bool state)
    {
        switch(control)
        {
            case GameControl::ACTION:
                action = state;
                break;
            case GameControl::UP:
                if(state)
                    up = 100000;
                else
                    up = 0;
                break;
            case GameControl::DOWN:
                if(state)
                    down = 100000;
                else
                    down = 0;
                break;
            case GameControl::LEFT:
                if(state)
                    left = 100000;
                else
                    left = 0;
                break;
            case GameControl::RIGHT:
                if(state)
                    right = 100000;
                else
                    right = 0;
                break;
        }
    }
    bool PlayerInputStruct::pollEvents(PlayerInputStruct &oldInputs, GameEvent &e)
    {
        if(oldInputs.action != action)
        {
            e.setControl(GameControl::ACTION);
            e.setState(action);
            return true;
        }
        return false;
    }
}
