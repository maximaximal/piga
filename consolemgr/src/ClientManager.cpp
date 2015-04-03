#include <ClientManager.hpp>

ClientManager::ClientManager(QObject *parent) : QObject(parent)
{

}
ClientManager::~ClientManager()
{
    for(auto &client : m_clients)
    {
        delete client;
        client = nullptr;
    }
}
Client *ClientManager::newConnection(const QString &host, int port, const QString &user, const QString &pass)
{
    Client *client = new Client(this);

    client->connectToConsole(host, port, user, pass);

    m_clients.push_back(client);

    return client;
}
ClientManager::ClientList ClientManager::getClients()
{
    return m_clients;
}

