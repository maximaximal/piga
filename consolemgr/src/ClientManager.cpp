#include <ClientManager.hpp>
#include <QDebug>

ClientManager::ClientManager(QObject *parent) : QAbstractListModel(parent)
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

    client->setName("Unknown");
    client->connectToConsole(host, port);

    beginInsertRows(QModelIndex(), m_clients.size(), m_clients.size());
    m_clients.push_back(client);
    endInsertRows();

    return client;
}
ClientManager::ClientList ClientManager::getClients()
{
    return m_clients;
}
int ClientManager::rowCount(const QModelIndex &parent) const
{
    return m_clients.size();
}
QVariant ClientManager::data(const QModelIndex &index, int role) const
{
    QVariant result;
    Client *client = m_clients[index.row()];
    switch(role)
    {
        case AddressRole:
            result = client->address();
            break;
        case NameRole:
            result = client->name();
            break;
        case NetworkClient:
            result.setValue(client);
            break;
    }
    return result;
}
QHash<int, QByteArray> ClientManager::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[AddressRole] = "address";
    roles[NameRole] = "name";
    roles[NetworkClient] = "netClient";
    return roles;
}
void ClientManager::update()
{
    bool update = false;
    for(std::size_t i = 0; i < m_clients.size(); ++i)
    {
        update = m_clients[i]->update();
        if(update)
        {
            //The data of the client has been changed!
            //Issue the dataChanged signal, so the Model updates its views.

            //dataChanged(QModelIndex(), QModelIndex());
        }
    }
}
