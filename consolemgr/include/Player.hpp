#pragma once

#include <memory>
#include <QObject>

namespace piga
{
    class Player;
}

class Player : public QObject
{
        Q_OBJECT
        Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

    public:
        Player();
        Player(const Player &other);
        Player(std::shared_ptr<piga::Player> player);
        ~Player();

        std::shared_ptr<piga::Player> getPlayer() const;
        void setPlayer(std::shared_ptr<piga::Player> player);

        QString name();
        void setName(QString name);
    signals:
        void nameChanged(QString name);
    private:
        std::shared_ptr<piga::Player> m_player;
};

Q_DECLARE_METATYPE(Player)
