#include <piga/Player.hpp>
#include <piga/Definitions.hpp>
#include <iostream>

using std::cout;
using std::endl;

namespace piga
{
    Player::Player(const char *username, bool active, int playerID)
    {
        setName(username);
        m_active = active;
        m_playerID = playerID;
    }
    bool Player::isAuthorized()
    {
        boost::shared_lock<boost::shared_mutex> lock(m_authorizedMutex);

        return m_authorized;
    }
    void Player::authorize(const std::string &password)
    {
        boost::upgrade_lock<boost::shared_mutex> lock(m_authorizedMutex);
        boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);
    }
    void Player::setName(const char *name)
    {
        boost::upgrade_lock<boost::shared_mutex> lock(m_nameMutex);
        boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);

        if(strlen(name) > 255)
        {
            cout << PIGA_DEBUG_PRESTRING << "Username was longer than 255 characters! Truncated the name to fit the maximum size." << endl;
            strncpy(m_name, name, 254);
        }
        else
        {
            strcpy(m_name, name);
        }
    }
    void Player::setActive(bool active)
    {
        boost::upgrade_lock<boost::shared_mutex> lock(m_activeMutex);
        boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);

        m_active = active;
    }
    void Player::setPlayerID(int id)
    {
        m_playerID = id;
    }
    const char* Player::getName()
    {
        boost::shared_lock<boost::shared_mutex> lock(m_nameMutex);

        return m_name;
    }
    int Player::getPlayerID()
    {
        return m_playerID;
    }
    bool Player::isActive()
    {
        boost::shared_lock<boost::shared_mutex> lock(m_activeMutex);
        return m_active;
    }
}
