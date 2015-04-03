#include <NetworkedClient/PlayerManager.hpp>

namespace NetworkedClient
{
    PlayerManager::PlayerManager()
    {

    }
    PlayerManager::~PlayerManager()
    {

    }
    void PlayerManager::set(std::shared_ptr<piga::Player> &player, unsigned int id)
    {
        m_players[id] = player;
    }
    std::shared_ptr<piga::Player> PlayerManager::get(unsigned int id)
    {
        if(m_players.count(id) > 0)
        {
            return m_players[id];
        }
        else
        {
            throw(PlayerNotFound(("The Player with the ID \"" + std::to_string(id) + "\" was not found!").c_str()));
        }
    }

    void PlayerManager::clear()
    {
        m_players.clear();
    }
    PlayerManager::PlayerMap &PlayerManager::getPlayers()
    {
        return m_players;
    }
    unsigned int PlayerManager::size()
    {
        unsigned int maxID = 0;
        for(auto player : m_players)
        {
            if(player.first > maxID)
                maxID = player.first;
        }
        return maxID;
    }


    PlayerManager::PlayerNotFound::PlayerNotFound(const char *message)
    {
        m_msg = message;
    }
    PlayerManager::PlayerNotFound::~PlayerNotFound()
    {

    }
    const char *PlayerManager::PlayerNotFound::what() const noexcept
    {
        return m_msg;
    }
}

