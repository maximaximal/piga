#include <NetworkedClient/Client.hpp>
#include <Client.hpp>
#include <QDebug>


namespace NetCl = NetworkedClient;

Client::Client(QObject *parent) : QObject(parent)
{
    m_netPlayerManager = std::make_shared<NetCl::PlayerManager>();
}
Client::Client(const Client &other)
{
    if(!other.getPlayerManager())
    {
        m_netPlayerManager = std::make_shared<NetCl::PlayerManager>();
    }
    else
    {
        m_netPlayerManager = other.getPlayerManager();
    }
    m_netClient = other.getNetClient();
}
Client::~Client()
{
    while(!m_players.isEmpty())
    {
        delete m_players.last();
        m_players.erase(m_players.end());
    }
}
void Client::connectToConsole(const QString &host, int port)
{
    if(m_netClient)
        m_netClient.reset();

    m_netPlayerManager->clear();
    m_netClient = std::make_shared<NetCl::Client>(m_netPlayerManager);

    m_netClient->setServerAddress(host.toStdString());
    m_netClient->setServerPort(port);

    m_netClient->handshakeCompleted().connect(sigc::mem_fun(this, &Client::handshakeCompleted));

    m_netClient->connect();
}
QString Client::name() const
{
    return m_name;
}
QString Client::address() const
{
    return QString::fromStdString(m_netClient->getServerAddress());
}
int Client::port() const
{
    return m_netClient->getServerPort();
}
void Client::setName(QString name)
{
    m_name = name;
    nameChanged(name);
}
bool Client::update()
{
    if(m_netClient)
        return m_netClient->update();
    return false;
}
Client::StatusCode Client::status() const
{
    return static_cast<StatusCode>(m_netClient->getLoginStatus());
}
QList<QObject *> *Client::players()
{
    return &m_players;
}
void Client::setStatus(Client::StatusCode status)
{
    m_netClient->setLoginStatus(static_cast<NetCl::Client::LoginResponse>(status));
}
std::shared_ptr<NetworkedClient::Client> Client::getNetClient() const
{
    return m_netClient;
}
std::shared_ptr<NetworkedClient::PlayerManager> Client::getPlayerManager() const
{
    return m_netPlayerManager;
}
void Client::handshakeCompleted()
{
    setName(QString::fromStdString(m_netClient->getServerName()));
    this->clientConnected();

    for(auto &pigaPlayer : m_netClient->getPlayerManager()->getPlayers())
    {
        m_players.push_back(new Player(pigaPlayer.second));
    }
}
