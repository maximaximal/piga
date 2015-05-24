#pragma once

#include <memory>

#include <piga/PlayerManager.hpp>

#include <QObject>
#include <QAbstractListModel>

namespace pigaco
{
class Players : public QAbstractListModel
{
        Q_OBJECT
    public:
        Players(std::shared_ptr<piga::PlayerManager> &playerManager);
        Players(const Players &other);
        Players();
        virtual ~Players();

        enum PlayerRoles {
            NameRole = Qt::UserRole + 1,
            IDRole
        };

        QHash<int, QByteArray> roleNames() const;
        virtual int rowCount(const QModelIndex &parent) const;
        virtual QVariant data(const QModelIndex &index, int role) const;

        std::shared_ptr<piga::PlayerManager> getPlayerManager() const;
    public Q_SLOTS:
        void playerNameChanged(QString name, int playerID);
    private:
        std::shared_ptr<piga::PlayerManager> m_playerManager;
};
}

Q_DECLARE_METATYPE(pigaco::Players)
