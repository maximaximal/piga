#include <pigaco/DirectoryScanner.hpp>
#include <boost/filesystem.hpp>
#include <easylogging++.h>

#include <QDir>

namespace fs = boost::filesystem;

namespace pigaco
{
    DirectoryScanner::DirectoryScanner(const DirectoryScanner &dirScanner)
    {
        m_host = dirScanner.getHost();
        m_directory = dirScanner.getDirectory();
    }
    DirectoryScanner::DirectoryScanner(std::shared_ptr<piga::Host> host)
            : m_host(host)
    {

    }
    DirectoryScanner::~DirectoryScanner()
    {

    }
    QHash<int, QByteArray> DirectoryScanner::roleNames() const {
        QHash<int, QByteArray> roles;
        roles[DescriptionRole] = "description";
        roles[NameRole] = "name";
        roles[VersionRole] = "version";
        roles[AuthorRole] = "author";
        roles[GameHostRole] = "game";
        roles[BackgroundImageRole] = "backgroundImage";
        roles[LogoImageRole] = "logoImage";
        return roles;
    }
    void DirectoryScanner::scanDirectory(const std::string &dir)
    {
        m_directory = dir;
        LOG(INFO) << "Scanning directory \"" << dir << "\".";
        if(!fs::exists(dir))
        {
            LOG(FATAL) << "The path \"" << dir.c_str() << "\" does not exist!";
            return;
        }
        if(!fs::is_directory(dir))
        {
            LOG(FATAL) << "The path \"" << dir.c_str() << "\" is not a directory!";
            return;
        }
        fs::directory_iterator end_it;
		for(fs::directory_iterator it(dir); it != end_it; ++it)
        {
            if(fs::is_directory(it->status()))
            {
                addGame(it->path().string());
            }
        }
        LOG(INFO) << "Scan completed!";
    }
    void DirectoryScanner::addGame(const std::string &dir)
    {
        GameHostStarter *gameHost = new GameHostStarter();
        gameHost->loadFromDirectory(dir);
        gameHost->setHost(m_host);

        std::shared_ptr<Game> game = std::make_shared<Game>(gameHost);

        m_games.push_back(game);
    }
    void DirectoryScanner::setHost(std::shared_ptr<piga::Host> host)
    {
        m_host = host;
    }
    std::shared_ptr<Game> DirectoryScanner::getGame(const std::string &dir)
    {
        return getGame(QString::fromStdString(dir));
    }
    std::shared_ptr<Game> DirectoryScanner::getGame(const QString &dir)
    {
        std::shared_ptr<Game> game;
        game = lookupGame(dir);
        if(game)
        {
            return game;
        }
        game = lookupGame(QString::fromStdString(m_directory) + "/" + dir);
        if(game)
        {
            return game;
        }
        for(auto &gameO : m_games)
        {
            if(QString::fromStdString(gameO->getConfig(piga::GameHost::Name)) == dir)
            {
                return gameO;
            }
        }
        LOG(FATAL) << "Game in \"" << dir.toStdString() << "\" not found! Returning the first game.";
        return m_games.first();
    }
    std::shared_ptr<Game> DirectoryScanner::lookupGame(const QString &dir)
    {
        for(auto &game : m_games)
        {
            if(game->getConfig(Game::Directory) == dir)
                return game;
        }
    }
    std::shared_ptr<piga::Host> DirectoryScanner::getHost() const
    {
        return m_host;
    }
    const std::string &DirectoryScanner::getDirectory() const
    {
        return m_directory;
    }
    int DirectoryScanner::rowCount(const QModelIndex &parent) const
    {
        return m_games.size();
    }

    QVariant DirectoryScanner::data(const QModelIndex &index, int role) const
    {
        QVariant result;
        std::shared_ptr<Game> game = m_games[index.row()];
        switch(role)
        {
            case NameRole:
                result = game->getConfig(Game::Name);
                break;
            case VersionRole:
                result = game->getConfig(Game::Version);
                break;
            case AuthorRole:
                result = game->getConfig(Game::Author);
                break;
            case DescriptionRole:
                result = game->getConfig(Game::Description);
                break;
            case GameHostRole:
                result.setValue(game.get());
                break;
            case BackgroundImageRole:
                result = QDir::currentPath() + "/" + game->getConfig(Game::BackgroundImage);
                break;
            case LogoImageRole:
                result = QDir::currentPath() + "/" + game->getConfig(Game::Logo);
                break;
        }

        return result;
    }
}
