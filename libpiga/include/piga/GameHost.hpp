#ifndef LIBPIGA_PIGA_GAMEHOST_HPP_INCLUDED
#define LIBPIGA_PIGA_GAMEHOST_HPP_INCLUDED

#include <map>
#include <memory>
#include <string>

#include <piga/GameEvent.hpp>

namespace piga
{
    class Host;

    /**
     * @brief Holds an instance of a game. 
     * 
     * Games/Apps are loaded, run, and managed through this class.
     */
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
                InMainGamesList,

                _COUNT
            };

            GameHost();
            virtual ~GameHost();

            void setHost(std::shared_ptr<Host> host);
            void loadFromDirectory(const std::string &directory);
            void start();
            void exit();

            bool isValid();
            virtual bool isRunning(bool fsCheck = false);
            void invalidate(bool state = false);
            void setRunning(bool state);

            const std::string& getConfig(ConfigValue id);
            void setConfig(ConfigValue id, const std::string &value);
            
            void sendGameEvent(const piga::GameEvent &event);

        protected:
            virtual void startGame(const std::string &command, const std::string &arguments);
            bool m_running = false;
        private:
            std::map<ConfigValue, std::string> m_config;
            std::map<int, std::map<piga::GameControl, std::string>> m_keyboardMappings;
            std::shared_ptr<Host> m_host;
            bool m_valid = true;
            std::string m_currentPath;
    };
}

#endif
