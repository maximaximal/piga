#include <piga/PlayerManager.hpp>
#include <piga/Definitions.hpp>
#include <piga/Host.hpp>

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
        if(m_players != nullptr)
            delete m_players;
    }
    void PlayerManager::init()
    {
        if(m_players != nullptr)
            delete m_players;

        using namespace boost::interprocess;
        m_players = new boost::interprocess::managed_shared_memory(open_only,
                                                                   Host::getPlayersSharedMemoryName());

        std::pair<Player*, std::size_t> p =
                m_players->find<Player>("Player");

        m_mappedPlayers = p.first;
        m_mappedPlayersNum = p.second;
    }
    Player *PlayerManager::getPlayer(int playerID)
    {
        return &m_mappedPlayers[playerID];
    }
    int PlayerManager::size()
    {
        return m_mappedPlayersNum;
    }
}
