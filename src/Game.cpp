#include <pigaco/Game.hpp>

namespace pigaco
{

Game::Game()
{
    m_gameHost = new piga::GameHost();
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
void Game::start()
{
    m_gameHost->start();
}
void Game::exit()
{
    m_gameHost->exit();
}
QString Game::getConfig(ConfigValue id)
{
    return QString::fromStdString(m_gameHost->getConfig(
                                      static_cast<piga::GameHost::ConfigValue>(id)));
}

}
