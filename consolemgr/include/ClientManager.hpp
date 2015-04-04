#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include <Client.hpp>
#include <QObject>
#include <QList>
#include <QTimer>

class ClientManager : public QObject
{
        Q_OBJECT
        Q_PROPERTY(ClientList clients READ getClients)
    public:
        typedef QList<Client*> ClientList;

        explicit ClientManager(QObject *parent = 0);
        ~ClientManager();

        Q_INVOKABLE Client* newConnection(const QString &host, int port);

        ClientList getClients();
    signals:

    public slots:
        void update();
    private:
        ClientList m_clients;
        QTimer *m_updateTimer;
};

#endif // CLIENTMANAGER_HPP
