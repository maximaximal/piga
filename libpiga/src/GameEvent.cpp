#include <piga/GameEvent.hpp>

namespace piga
{
    GameEvent::GameEvent(const GameEvent &gameEvent)
    {
        (*this) = gameEvent;
    }
    GameEvent::GameEvent(int playerID)
        : m_playerID(playerID), m_type(GameEventType::Undefined)
    {

    }
    GameEvent::GameEvent(int playerID, const event::GameInput &gameInput)
        : m_playerID(playerID), gameInput(gameInput), m_type(GameEventType::GameInput)
    {

    }
    GameEvent::GameEvent(int playerID, const event::TextInput &textInput)
        : m_playerID(playerID), textInput(textInput), m_type(GameEventType::TextInput)
    {

    }
    GameEvent::~GameEvent()
    {

    }
    void GameEvent::setPlayerID(int playerID)
    {
        m_playerID = playerID;
    }
    int GameEvent::playerID() const
    {
        return m_playerID;
    }
    GameEvent::GameEventType GameEvent::type() const
    {
        return m_type;
    }
    GameEvent &GameEvent::operator=(const GameEvent &otherEvent)
    {
        m_playerID = otherEvent.playerID();
        m_type = otherEvent.type();
        switch(otherEvent.type())
        {
            case GameInput:
                gameInput = otherEvent.gameInput;
                break;
            case TextInput:
                textInput = otherEvent.textInput;
                break;
            default:
                //Do nothing
                break;
        }
        return *this;
    }
    void GameEvent::operator=(const event::GameInput &gameInput)
    {
        this->gameInput = gameInput;
        m_type = GameInput;
    }
    void GameEvent::operator=(const event::TextInput &textInput)
    {
        this->textInput = textInput;
        m_type = TextInput;
    }
}
