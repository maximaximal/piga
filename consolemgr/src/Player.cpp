#include <Player.hpp>
#include <piga/Player.hpp>


Player::Player()
{
    m_player = std::make_shared<piga::Player>();
}
Player::Player(const Player &other)
{
    m_player = other.getPlayer();
}
Player::Player(std::shared_ptr<piga::Player> player)
{
    m_player = player;
}
Player::~Player()
{

}
std::shared_ptr<piga::Player> Player::getPlayer() const
{
    return m_player;
}
void Player::setPlayer(std::shared_ptr<piga::Player> player)
{
    m_player = player;
}
QString Player::name()
{
    return QString(m_player->getName());
}
void Player::setName(QString name)
{
    m_player->setName(name.toStdString().c_str());
}
