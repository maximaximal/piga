#include <NetworkedClient/Client.hpp>
#include <Client.hpp>

namespace NetCl = NetworkedClient;

Client::Client(QObject *parent) : QObject(parent)
{
    m_netPlayerManager = std::make_shared<NetCl::PlayerManager>();
}
Client::~Client()
{
    if(m_netClient != nullptr)
        delete m_netClient;
}
void Client::connectToConsole(const QString &host, int port, const QString &user, const QString &pass)
{
    if(m_netClient != nullptr)
        delete m_netClient;

    m_netPlayerManager->clear();
    m_netClient = new NetCl::Client(m_netPlayerManager);

    m_netClient->setServerAddress(host.toStdString());
    m_netClient->setServerPort(port);

    m_netClient->connect();
}
QString Client::name() const
{
    return m_name;
}
void Client::setName(QString name)
{
    m_name = name;
}
