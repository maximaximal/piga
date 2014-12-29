#pragma once

#include <string>
#include <map>
#include <piga/GameHost.hpp>

namespace pigaco
{
    class DirectoryScanner
    {
        public:
            typedef std::map<std::string, std::shared_ptr<piga::GameHost> > GameMap;
            DirectoryScanner();
            virtual ~DirectoryScanner();

            void scanDirectory(const std::string &dir);
			void addGame(const std::string &dir);

			GameMap& getGames();
            std::shared_ptr<piga::GameHost> getGame(const std::string &dir);
		private:
            std::string m_directory = "";
            GameMap m_games;
    };
}
