#include <pigaco/Players.hpp>

namespace pigaco
{

Players::Players(std::shared_ptr<piga::PlayerManager> &playerManager)
    : m_playerManager(playerManager), QAbstractListModel()
{

}

Players::Players(const Players &other)
    : QAbstractListModel()
{
    m_playerManager = other.getPlayerManager();
}

Players::Players()
    : QAbstractListModel()
{
    m_playerManager = std::make_shared<piga::PlayerManager>();
}

Players::~Players()
{

}

QHash<int, QByteArray> Players::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "playerName";
    roles[IDRole] = "playerID";
    return roles;
}

int Players::rowCount(const QModelIndex &parent) const
{
    return m_playerManager->size();
}

QVariant Players::data(const QModelIndex &index, int role) const
{
    QVariant result;
    switch(role)
    {
        case NameRole:
            result = QString(m_playerManager->getPlayer(index.row())->getName());
            break;
        case IDRole:
            result = index.row();
            break;
    }
    return result;
}

std::shared_ptr<piga::PlayerManager> Players::getPlayerManager() const
{
    return m_playerManager;
}

void Players::playerNameChanged(QString name, int playerID)
{
    if(playerID >= 0 && playerID < m_playerManager->size())
    {
        m_playerManager->getPlayer(playerID)->setName(name.toStdString().c_str());
    }
}

}
