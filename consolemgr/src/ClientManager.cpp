#include <ClientManager.hpp>

ClientManager::ClientManager(QObject *parent) : QObject(parent)
{
    m_updateTimer = new QTimer(this);
    connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(update()));
    m_updateTimer->start(16.666);
}
ClientManager::~ClientManager()
{
    for(auto &client : m_clients)
    {
        delete client;
        client = nullptr;
    }
    delete m_updateTimer;
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
    for(auto &client : m_clients)
    {
        client->update();
    }
}

