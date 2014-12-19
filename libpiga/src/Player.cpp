#include <piga/Player.hpp>

namespace piga
{
    Player::Player(int playerID, const std::string &username)
    	: m_playerID(playerID), m_name(username)
    {

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
    void Player::setName(const std::string &name)
    {
        boost::upgrade_lock<boost::shared_mutex> lock(m_nameMutex);
        boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);

        m_name = name;
    }
    const std::string &Player::getName()
    {
        boost::shared_lock<boost::shared_mutex> lock(m_nameMutex);

        return m_name;
    }
    int Player::getPlayerID()
    {
        return m_playerID;
    }
}
