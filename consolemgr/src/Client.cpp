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
void Client::connectToConsole(const QString &host, int port)
{
    if(m_netClient != nullptr)
        delete m_netClient;

    m_netPlayerManager->clear();
    m_netClient = new NetCl::Client(m_netPlayerManager);

    m_netClient->setServerAddress(host.toStdString());
    m_netClient->setServerPort(port);

    m_netClient->handshakeCompleted().connect(sigc::mem_fun(this, &Client::handshakeCompleted));

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
void Client::update()
{
    if(m_netClient != nullptr)
        m_netClient->update();
}
void Client::handshakeCompleted()
{
    this->clientConnected();
}
