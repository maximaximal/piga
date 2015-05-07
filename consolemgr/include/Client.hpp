#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <memory>
#include <QObject>
#include <Player.hpp>

namespace NetworkedClient
{
    class PlayerManager;
    class Client;
}

class Client : public QObject
{
        Q_OBJECT
        Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
        Q_PROPERTY(StatusCode status READ status)
        Q_PROPERTY(QList<QObject*>* players READ players)
    public:
        enum StatusCode
        {
            Success,
            WrongCredentials,
            ConnectionFailure,
            LoLoginPossible,
            NoMoreTries,
            UserIDNotExisting,
            UserIDAlreadyActive,

            _COUNT
        };

        Q_ENUMS(StatusCode)

        explicit Client(QObject *parent = 0);
        Client(const Client& other);
        ~Client();

        void connectToConsole(const QString &host, int port);

        QString name() const;
        QString address() const;
        int port() const;
        void setName(QString name);
        StatusCode status() const;
        QList<QObject*>* players();
        void setStatus(StatusCode status);
        std::shared_ptr<NetworkedClient::Client> getNetClient() const;
        std::shared_ptr<NetworkedClient::PlayerManager> getPlayerManager() const;
    signals:
        void clientConnected();
        void loginResponse(StatusCode response);
        void nameChanged(QString name);
    public slots:
        bool update();
    private:
        QString m_name;
        std::shared_ptr<NetworkedClient::Client> m_netClient;
        std::shared_ptr<NetworkedClient::PlayerManager> m_netPlayerManager;
        QList<QObject*> m_players;

        void handshakeCompleted();
};

Q_DECLARE_METATYPE_IMPL(Client)

#endif // CLIENT_HPP
