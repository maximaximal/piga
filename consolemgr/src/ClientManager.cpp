#include <ClientManager.hpp>
#include <QDebug>

ClientManager::ClientManager(QObject *parent) : QObject(parent)
{
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(16);
}
ClientManager::~ClientManager()
{
    for(auto &client : m_clients)
    {
        delete client;
        client = nullptr;
    }
    delete m_timer;
}
Client *ClientManager::newConnection(const QString &host, int port)
{
    Client *client = new Client(this);

    client->connectToConsole(host, port);

    m_clients.push_back(client);

    return client;
}
ClientManager::ClientList ClientManager::getClients()
{
    return m_clients;
}
void ClientManager::update()
{
    for(std::size_t i = 0; i < m_clients.size(); ++i)
    {
        m_clients[i]->update();
    }
}

