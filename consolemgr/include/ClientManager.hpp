#ifndef CLIENTMANAGER_HPP
#define CLIENTMANAGER_HPP

#include <Client.hpp>
#include <QObject>
#include <QList>
#include <QTimer>
#include <QAbstractListModel>

class ClientManager : public QAbstractListModel
{
        Q_OBJECT
        Q_PROPERTY(ClientList clients READ getClients)
    public:
        typedef QList<Client*> ClientList;

        explicit ClientManager(QObject *parent = 0);
        ClientManager(const ClientManager &other);
        ~ClientManager();

        enum ClientRoles {
            AddressRole = Qt::UserRole + 1,
            NameRole,
            NetworkClient
        };

        Q_INVOKABLE Client* newConnection(const QString &host, int port);

        ClientList getClients();

        virtual int rowCount(const QModelIndex &parent) const;
        virtual QVariant data(const QModelIndex &index, int role) const;
        virtual QHash<int, QByteArray> roleNames() const;
    public Q_SLOTS:
        void update();
    private:
        ClientList m_clients;
        QTimer *m_timer;
};

#endif // CLIENTMANAGER_HPP
