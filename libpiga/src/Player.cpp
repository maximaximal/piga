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
        m_edited = false;
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

        setEdited(true);
    }
    void Player::setActive(bool active)
    {
        boost::upgrade_lock<boost::shared_mutex> lock(m_activeMutex);
        boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);

        m_active = active;
        setEdited(true);
    }
    void Player::setPlayerID(int id)
    {
        m_playerID = id;

        setEdited(true);
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
    void Player::setEdited(bool state)
    {
        boost::upgrade_lock<boost::shared_mutex> lock(m_editedMutex);
        boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);

        m_edited = state;
    }
    bool Player::edited()
    {
        boost::shared_lock<boost::shared_mutex> lock(m_editedMutex);

        return m_edited;
    }
}
