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
Client *ClientManager::newConnection(const QString &host, const QString &user, const QString &pass)
{
    Client *client = new Client(this);

    client->connectToConsole(host, user, pass);

    m_clients.push_back(client);

    return client;
}
ClientManager::ClientList ClientManager::getClients()
{
    return m_clients;
}

