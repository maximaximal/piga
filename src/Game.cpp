#include <pigaco/Game.hpp>
#include <easylogging++.h>

namespace pigaco
{

Game::Game()
{
    m_gameHost = new piga::GameHost();
}
Game::Game(const Game &game)
{
    m_gameHost = game.getGameHost();
}
Game::Game(piga::GameHost *gameHost)
{
    m_gameHost = gameHost;
}
Game::~Game()
{
    delete m_gameHost;
}
bool Game::isRunning(bool fsCheck)
{
    return m_gameHost->isRunning(fsCheck);
}
bool Game::isValid()
{
    return m_gameHost->isValid();
}
void Game::setRunning(bool state)
{
    m_gameHost->setRunning(state);
}
piga::GameHost *Game::getGameHost() const
{
    return m_gameHost;
}
void Game::start()
{
    m_gameHost->start();
}
void Game::exit()
{
    m_gameHost->exit();
}
QString Game::getConfig(ConfigValue id) const
{
    return QString::fromStdString(m_gameHost->getConfig(
                                      static_cast<piga::GameHost::ConfigValue>(id)));
}
const std::string &Game::getConfig(piga::GameHost::ConfigValue id) const
{
    return m_gameHost->getConfig(id);
}
QString Game::getName() const
{
    return getConfig(ConfigValue::Name);
}
QString Game::getDescription() const
{
    return getConfig(ConfigValue::Description);
}
QString Game::getVersion() const
{
    return getConfig(ConfigValue::Version);
}
QString Game::getAuthor() const
{
    return getConfig(ConfigValue::Author);
}

}
