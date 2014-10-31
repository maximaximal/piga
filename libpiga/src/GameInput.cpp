#include <piga/GameInput.hpp>

namespace piga
{
    GameInput::GameInput()
    {
        
    }
    GameInput::~GameInput()
    {
        
    }
    void GameInput::update()
    {
        for(auto &input : m_playerInputs)
        {
            input.second->update();
        }
    }
    int GameInput::addPlayerInput(std::shared_ptr<PlayerInput> playerInput)
    {
        m_playerInputs[m_playerInputIdCounter] = playerInput;
        playerInput->setPlayerID(m_playerInputIdCounter);
        m_playerInputIdCounter++;
        return m_playerInputIdCounter - 1;
    }
    int GameInput::getPlayerCount()
    {
        return m_playerInputs.size();
    }
    const PlayerInput &GameInput::getPlayerInput(int id)
    {
        if(m_playerInputs.count(id) == 0)
			return *(m_playerInputs[id]);

        throw std::out_of_range("Player was not set at this ID!");
    }
    bool GameInput::pollEvent(GameEvent &gameEvent)
    {
        for(auto &playerInput : m_playerInputs)
        {
            if(playerInput.second->pollEvent(gameEvent))
            {
                return true;
            }
        }
        return false;
    }
}
