#include <Client.hpp>

Client::Client(QObject *parent) : QObject(parent)
{

}
Client::~Client()
{

}
void Client::connectToConsole(const QString &host, const QString &user, const QString &pass)
{

}
QString Client::name() const
{
    return m_name;
}
void Client::setName(QString name)
{
    m_name = name;
}
