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
            //Only if the input method has been specified earlier.
            if(method.second != nullptr)
            {
                if(method.second->hasChanged())
                {
                    event::GameInput input(method.first, method.second->isActive());
                    GameEvent event(m_playerID, input);
                    pushGameEvent(event);
                }
                method.second->update();
            }
        }
    }
    void PlayerInput::setInputMethod(InputMethod *method, GameControl control)
    {
        m_inputMethods[control] = method;
    }
    void PlayerInput::pushGameEvent(const GameEvent &gameEvent)
    {
        m_gameEvents.push_front(gameEvent);
    }
    PlayerInputStruct::PlayerInputStruct()
    {

    }
    PlayerInputStruct::~PlayerInputStruct()
    {

    }
    void PlayerInputStruct::fromGameEvent(GameEvent &e)
    {
        if(e.type() == GameEvent::GameInput)
        {
            fromGameEvent(e.gameInput.control(), e.gameInput.state());
        }
    }
    void PlayerInputStruct::fromGameEvent(const GameControl &control, bool state)
    {
        switch(control)
        {
            case GameControl::ACTION:
                setAction(state);
                break;
            case GameControl::UP:
                if(state)
                    setUp(100000);
                else
                    setUp(0);
                break;
            case GameControl::DOWN:
                if(state)
                    setDown(100000);
                else
                    setDown(0);
                break;
            case GameControl::LEFT:
                if(state)
                    setLeft(100000);
                else
                    setLeft(0);
                break;
            case GameControl::RIGHT:
                if(state)
                    setRight(100000);
                else
                    setRight(0);
                break;
            case GameControl::BUTTON1:
                setButton1(state);
                break;
            case GameControl::BUTTON2:
                setButton2(state);
                break;
            case GameControl::BUTTON3:
                setButton3(state);
                break;
            case GameControl::BUTTON4:
                setButton4(state);
                break;
            case GameControl::BUTTON5:
                setButton5(state);
                break;
            case GameControl::BUTTON6:
                setButton6(state);
                break;
            default:
                //Nothing to do; control is not handled by the automatic conversion.
                break;
        }
    }
    bool PlayerInputStruct::pollEvents(PlayerInputStruct &oldInputs, GameEvent &e)
    {
        //Check if the given event is already a game input event.
        if(e.type() != GameEvent::GameInput)
        {
            e = event::GameInput();
        }

        if(oldInputs.action() != action()) {
            e.gameInput.setControl(GameControl::ACTION);
            e.gameInput.setState(action());
            oldInputs.setAction(action());
            return true;
        }
        if(oldInputs.up() != up()) {
            e.gameInput.setControl(GameControl::UP);
            e.gameInput.setValue(up());
            oldInputs.setUp(up());
            return true;
        }
        if(oldInputs.down() != down()) {
            e.gameInput.setControl(GameControl::DOWN);
            e.gameInput.setValue(down());
            oldInputs.setDown(down());
            return true;
        }
        if(oldInputs.left() != left()) {
            e.gameInput.setControl(GameControl::LEFT);
            e.gameInput.setValue(left());
            oldInputs.setLeft(left());
            return true;
        }
        if(oldInputs.right() != right()) {
            e.gameInput.setControl(GameControl::RIGHT);
            e.gameInput.setValue(right());
            oldInputs.setRight(right());
            return true;
        }
        if(oldInputs.button1() != button1()) {
            e.gameInput.setControl(GameControl::BUTTON1);
            e.gameInput.setState(button1());
            oldInputs.setButton1(button1());
            return true;
        }
        if(oldInputs.button2() != button2()) {
            e.gameInput.setControl(GameControl::BUTTON2);
            e.gameInput.setState(button2());
            oldInputs.setButton2(button2());
            return true;
        }
        if(oldInputs.button3() != button3()) {
            e.gameInput.setControl(GameControl::BUTTON3);
            e.gameInput.setState(button3());
            oldInputs.setButton3(button3());
            return true;
        }
        if(oldInputs.button4() != button4()) {
            e.gameInput.setControl(GameControl::BUTTON4);
            e.gameInput.setState(button4());
            oldInputs.setButton4(button4());
            return true;
        }
        if(oldInputs.button5() != button5()) {
            e.gameInput.setControl(GameControl::BUTTON5);
            e.gameInput.setState(button5());
            oldInputs.setButton5(button5());
            return true;
        }
        if(oldInputs.button6() != button6()) {
            e.gameInput.setControl(GameControl::BUTTON6);
            e.gameInput.setState(button6());
            oldInputs.setButton6(button6());
            return true;
        }
        return false;
    }
    void PlayerInputStruct::setUp(int val)
    {
        boost::interprocess::ipcdetail::atomic_write32(&m_up, val);
    }
    void PlayerInputStruct::setDown(int val)
    {
        boost::interprocess::ipcdetail::atomic_write32(&m_down, val);
    }
    void PlayerInputStruct::setLeft(int val)
    {
        boost::interprocess::ipcdetail::atomic_write32(&m_left, val);
    }
    void PlayerInputStruct::setRight(int val)
    {
        boost::interprocess::ipcdetail::atomic_write32(&m_right, val);
    }
    void PlayerInputStruct::setAction(bool state)
    {
        setLikeBoolean(&m_action, state);
    }
    void PlayerInputStruct::setButton1(bool state)
    {
        setLikeBoolean(&m_button1, state);
    }
    void PlayerInputStruct::setButton2(bool state)
    {
        setLikeBoolean(&m_button2, state);
    }
    void PlayerInputStruct::setButton3(bool state)
    {
        setLikeBoolean(&m_button3, state);
    }
    void PlayerInputStruct::setButton4(bool state)
    {
        setLikeBoolean(&m_button4, state);
    }
    void PlayerInputStruct::setButton5(bool state)
    {
        setLikeBoolean(&m_button5, state);
    }
    void PlayerInputStruct::setButton6(bool state)
    {
        setLikeBoolean(&m_button6, state);
    }
    int PlayerInputStruct::up()
    {
        return boost::interprocess::ipcdetail::atomic_read32(&m_up);
    }
    int PlayerInputStruct::down()
    {
        return boost::interprocess::ipcdetail::atomic_read32(&m_down);
    }
    int PlayerInputStruct::left()
    {
        return boost::interprocess::ipcdetail::atomic_read32(&m_left);
    }
    int PlayerInputStruct::right()
    {
        return boost::interprocess::ipcdetail::atomic_read32(&m_right);
    }
    bool PlayerInputStruct::action()
    {
        return getLikeBoolean(&m_action);
    }
    bool PlayerInputStruct::button1()
    {
        return getLikeBoolean(&m_button1);
    }
    bool PlayerInputStruct::button2()
    {
        return getLikeBoolean(&m_button2);
    }
    bool PlayerInputStruct::button3()
    {
        return getLikeBoolean(&m_button3);
    }
    bool PlayerInputStruct::button4()
    {
        return getLikeBoolean(&m_button4);
    }
    bool PlayerInputStruct::button5()
    {
        return getLikeBoolean(&m_button5);
    }
    bool PlayerInputStruct::button6()
    {
        return getLikeBoolean(&m_button6);
    }
    void PlayerInputStruct::invertUp()
    {
        setUp(100000 - up());
    }
    void PlayerInputStruct::invertDown()
    {
        setDown(100000 - down());
    }
    void PlayerInputStruct::invertLeft()
    {
        setLeft(1000000 - left());
    }
    void PlayerInputStruct::invertRight()
    {
        setRight(100000 - right());
    }
    void PlayerInputStruct::invertAction()
    {
        setAction(!getLikeBoolean(&m_action));
    }
    void PlayerInputStruct::invertButton1()
    {
        setButton1(!getLikeBoolean(&m_button1));
    }
    void PlayerInputStruct::invertButton2()
    {
        setButton2(!getLikeBoolean(&m_button2));
    }
    void PlayerInputStruct::invertButton3()
    {
        setButton3(!getLikeBoolean(&m_button3));
    }
    void PlayerInputStruct::invertButton4()
    {
        setButton4(!getLikeBoolean(&m_button4));
    }
    void PlayerInputStruct::invertButton5()
    {
        setButton5(!getLikeBoolean(&m_button5));
    }
    void PlayerInputStruct::invertButton6()
    {
        setButton6(!getLikeBoolean(&m_button6));
    }
    void PlayerInputStruct::setLikeBoolean(volatile uint32_t *number, bool state)
    {
        if(state)
            boost::interprocess::ipcdetail::atomic_write32(number, 100000);
        else
            boost::interprocess::ipcdetail::atomic_write32(number, 0);
    }
    bool PlayerInputStruct::getLikeBoolean(volatile uint32_t *number)
    {
        if(boost::interprocess::ipcdetail::atomic_read32(number) == 100000)
            return true;
        else
            return false;
    }
}
