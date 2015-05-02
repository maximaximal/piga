#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <memory>
#include <QObject>

namespace NetworkedClient
{
    class Client;
    class PlayerManager;
}

class Client : public QObject
{
        Q_OBJECT
        Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
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

        explicit Client(QObject *parent = 0);
        ~Client();

        void connectToConsole(const QString &host, int port);

        QString name() const;
        QString address() const;
        int port() const;
        void setName(QString name);
        bool update();
    signals:
        void clientConnected();
        void loginResponse(StatusCode response);
        void nameChanged(QString name);
    private:
        QString m_name;
        NetworkedClient::Client *m_netClient = nullptr;
        std::shared_ptr<NetworkedClient::PlayerManager> m_netPlayerManager;

        void handshakeCompleted();
};

#endif // CLIENT_HPP
