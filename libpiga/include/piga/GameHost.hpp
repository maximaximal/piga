#ifndef LIBPIGA_PIGA_GAMEHOST_HPP_INCLUDED
#define LIBPIGA_PIGA_GAMEHOST_HPP_INCLUDED

#include <map>
#include <memory>
#include <string>

namespace piga
{
    class Host;

    class GameHost
    {
        public:
            enum ConfigValue
            {
                Name,
                Description,
                Version,
                Author,
                ProgramPath,
                Parameters,
                Directory,
                BackgroundImage,
                Logo,

                _COUNT
            };

            GameHost();
            virtual ~GameHost();

            void setHost(std::shared_ptr<Host> host);
            void loadFromDirectory(const std::string &directory);
            void start();
            void exit();

            bool isValid();
            bool isRunning();
            void invalidate(bool state = false);
            void setRunning(bool state);

            const std::string& getConfig(ConfigValue id);
            void setConfig(ConfigValue id, const std::string &value);
        private:
            std::map<ConfigValue, std::string> m_config;
            std::shared_ptr<Host> m_host;
            bool m_valid = true;
            bool m_running = false;
            std::string m_currentPath;
    };
}

#endif
