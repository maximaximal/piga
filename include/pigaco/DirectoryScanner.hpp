#pragma once

#include <string>
#include <map>
#include <piga/GameHost.hpp>
#include <pigaco/Game.hpp>

#include <QAbstractListModel>

namespace pigaco
{
    class DirectoryScanner : public QAbstractListModel
    {
        Q_OBJECT

        public:
            DirectoryScanner();
            DirectoryScanner(const DirectoryScanner &dirScanner);
            DirectoryScanner(std::shared_ptr<piga::Host> host);
            virtual ~DirectoryScanner();

            enum GameRoles {
                NameRole = Qt::UserRole + 1,
                DescriptionRole,
                AuthorRole,
                VersionRole,
                GameHostRole,
                BackgroundImageRole,
                LogoImageRole
            };

            QHash<int, QByteArray> roleNames() const;

            void scanDirectory(const std::string &dir);
			void addGame(const std::string &dir);

            void setHost(std::shared_ptr<piga::Host> host);
            std::shared_ptr<Game> getGame(const std::string &dir);
            std::shared_ptr<Game> getGame(const QString &dir);
            std::shared_ptr<Game> lookupGame(const QString &dir);
            std::shared_ptr<piga::Host> getHost() const;
            const std::string& getDirectory() const;

            virtual int rowCount(const QModelIndex &parent) const;
            virtual QVariant data(const QModelIndex &index, int role) const;
		private:
            std::string m_directory = "";
            std::shared_ptr<piga::Host> m_host;
            QList<std::shared_ptr<Game> > m_games;
    };

}

Q_DECLARE_METATYPE(pigaco::DirectoryScanner)
