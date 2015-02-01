#include <piga/PlayerManager.hpp>
#include <piga/Definitions.hpp>

#include <iostream>
using std::cout;
using std::endl;

namespace piga
{
    PlayerManager::PlayerManager()
    {

    }
    PlayerManager::~PlayerManager()
    {

    }
    void PlayerManager::clear()
    {
        m_players.clear();
    }
    std::shared_ptr<Player> PlayerManager::get(unsigned int playerID)
    {
        if(m_players.count(playerID) > 0)
            return m_players[playerID];

        cout << PIGA_DEBUG_PRESTRING << "PlayerID " << playerID << " not found! Returning player 0." << endl;

        return m_players[0];
    }
    void PlayerManager::set(std::shared_ptr<Player> player, unsigned int id)
    {
        if(m_players.count(id) > 0)
        {
            cout << PIGA_DEBUG_PRESTRING << "The player with the ID " << id << " already existed!" << endl;
            cout << PIGA_DEBUG_PRESTRING << "Overriding player \"" << m_players[id]->getName() << "\" with player \"" << player->getName() << "\"." << endl;
        }
        m_players[id] = player;
    }
    std::size_t PlayerManager::size()
    {
        return m_players.size();
    }
    std::map<unsigned int, std::shared_ptr<Player> >& PlayerManager::getPlayers()
    {
        return m_players;
    }
}
