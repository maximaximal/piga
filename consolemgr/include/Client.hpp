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
        Q_PROPERTY(QString name READ name WRITE setName)
    public:
        enum StatusCode
        {
            Success,
            ConnectionFailure,
            CouldNotFindHost,
            WrongCredentials,

            _COUNT
        };

        explicit Client(QObject *parent = 0);
        ~Client();

        void connectToConsole(const QString &host, int port, const QString &user, const QString &pass);

        QString name() const;
        void setName(QString name);
    signals:
        void clientConnected();
    public slots:
    private:
        QString m_name;
        NetworkedClient::Client *m_netClient = nullptr;
        std::shared_ptr<NetworkedClient::PlayerManager> m_netPlayerManager;
};

#endif // CLIENT_HPP
