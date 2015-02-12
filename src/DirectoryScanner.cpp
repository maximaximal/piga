#include <pigaco/DirectoryScanner.hpp>
#include <boost/filesystem.hpp>
#include <easylogging++.h>

namespace fs = boost::filesystem;

namespace pigaco
{
    DirectoryScanner::DirectoryScanner(std::shared_ptr<piga::Host> host)
        : m_host(host)
    {

    }
    DirectoryScanner::~DirectoryScanner()
    {

    }
    void DirectoryScanner::scanDirectory(const std::string &dir)
    {
        m_directory = dir;
        LOG(INFO) << "Scanning directory \"" << dir << "\".";
        if(!fs::exists(dir))
        {
            LOG(FATAL) << "The path \"" << dir << "\" does not exist!";
            return;
        }
        if(!fs::is_directory(dir))
        {
            LOG(FATAL) << "The path \"" << dir << "\" is not a directory!";
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
        std::shared_ptr<piga::GameHost> gameHost = std::make_shared<piga::GameHost>();
        gameHost->loadFromDirectory(dir);
        gameHost->setHost(m_host);
        m_games[dir] = gameHost;
    }
    DirectoryScanner::GameMap &DirectoryScanner::getGames()
    {
		return m_games;
    }
    std::shared_ptr<piga::GameHost> DirectoryScanner::getGame(const std::string &dir)
    {
		if(m_games.count(dir) > 0)
        {
            return m_games[dir];
        }
        if(m_games.count(m_directory + "/" + dir) > 0)
        {
            return m_games[m_directory + "/" + dir];
        }
        for(auto &game : m_games)
        {
            if(game.second->getConfig(piga::GameHost::Name) == dir)
            {
                return game.second;
            }
        }
        LOG(FATAL) << "Game in \"" << dir << "\" not found! Returning the first game.";
        return (*m_games.begin()).second;
    }
}
