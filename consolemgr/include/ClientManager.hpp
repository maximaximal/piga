#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include <Client.hpp>
#include <QObject>
#include <QList>

class ClientManager : public QObject
{
        Q_OBJECT
        Q_PROPERTY(ClientList clients READ getClients)
    public:
        typedef QList<Client*> ClientList;

        explicit ClientManager(QObject *parent = 0);
        ~ClientManager();

        Q_INVOKABLE Client* newConnection(const QString &host, int port, const QString &user, const QString &pass);

        ClientList getClients();
    signals:

    public slots:

    private:
        ClientList m_clients;
};

#endif // CLIENTMANAGER_HPP
