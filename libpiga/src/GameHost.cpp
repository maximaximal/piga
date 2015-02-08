#include <piga/GameHost.hpp>
#include <sstream>
#include <yaml-cpp/yaml.h>
#include <boost/filesystem.hpp>
#include <iostream>
#include <piga/Definitions.hpp>

using std::cout;
using std::endl;

namespace piga
{
    GameHost::GameHost()
    {

    }
    GameHost::~GameHost()
    {

    }
    void GameHost::setHost(std::shared_ptr<Host> host)
    {
        m_host = host;
    }
    void GameHost::loadFromDirectory(const std::string &directory)
    {
        setConfig(Directory, directory);
        cout << PIGA_DEBUG_PRESTRING << "Loading game from \"" << directory << "\"." << endl;

        YAML::Node config;

        try
        {
            config = YAML::LoadAllFromFile(directory + "/config.yml").front();
        }
        catch
            (std::exception &e)
        {
            cout << PIGA_DEBUG_PRESTRING << "The config.yml in \"" << directory << "\" could not be loaded!" << endl;
            return;
        }

        if(config["Name"])
            setConfig(Name, config["Name"].as<std::string>());
        else
        {
            setConfig(Name, "Unnamed");
            cout << PIGA_DEBUG_PRESTRING << "The config.yml in \"" << directory << "\" has no Name node!" << endl;
        }

        if(config["Description"])
            setConfig(Description, config["Description"].as<std::string>());
        else
        {
            setConfig(Description, "A piga game.");
            cout << PIGA_DEBUG_PRESTRING << "The config.yml in \"" << directory << "\" has no Description node!" << endl;
        }

        if(config["Version"])
            setConfig(Version, config["Version"].as<std::string>());
        else
        {
            setConfig(Version, "1.0");
            cout << PIGA_DEBUG_PRESTRING << "The config.yml in \"" << directory << "\" has no Version node!" << endl;
        }
        
        if(config["Author"])
            setConfig(Author, config["Author"].as<std::string>());
        else
        {
            setConfig(Author, "Unknown");
            cout << PIGA_DEBUG_PRESTRING << "The config.yml in \"" << directory << "\" has no Author node!" << endl;
        }
        
        if(config["BackgroundImage"])
            setConfig(BackgroundImage, getConfig(Directory) + config["BackgroundImage"].as<std::string>());
        else
        {
            setConfig(BackgroundImage, "");
            cout << PIGA_DEBUG_PRESTRING << "The config.yml in \"" << directory << "\" has no BackgroundImage node!" << endl;
        }
        
        if(config["Logo"])
            setConfig(Logo, getConfig(Directory) + config["Logo"].as<std::string>());
        else
        {
            setConfig(Logo, "");
            cout << PIGA_DEBUG_PRESTRING << "The config.yml in \"" << directory << "\" has no Logo node!" << endl;
        }

        if(config["Parameters"])
            setConfig(Parameters, config["Parameters"].as<std::string>());
        else
        {
            setConfig(Parameters, "");
            cout << PIGA_DEBUG_PRESTRING << "The config.yml in \"" << directory << "\" has no Parameters node!" << endl;
        }

        if(config["ProgramPath"])
            setConfig(ProgramPath, config["ProgramPath"].as<std::string>());
        else
        {
            setConfig(ProgramPath, "Client");
            cout << PIGA_DEBUG_PRESTRING << "The config.yml in \"" << directory << "\" has no ProgramPath node!" << endl;
        }

        cout << PIGA_DEBUG_PRESTRING << "Loaded game \"" << getConfig(Name) << "\" from directory \"" << directory
             << "\"." << endl;
    }
    void GameHost::start()
    {
        if(isValid())
        {
            if(isRunning())
            {
                cout << PIGA_DEBUG_PRESTRING << "Program \"" << getConfig(Name) << "\" in directory \"" << getConfig(Directory)
                     << "\" is already running!" << endl;
                return;
            }
            cout << PIGA_DEBUG_PRESTRING << "Starting program \"" << getConfig(Name) << "\"" << endl;

            m_currentPath = boost::filesystem::current_path().string();
            boost::filesystem::current_path(getConfig(Directory));

            std::stringstream command;
            command << "./" << getConfig(ProgramPath);
            command << " ";
            command << getConfig(Parameters);
            command << " &";

            std::string systemCmd = command.str();

            cout << PIGA_DEBUG_PRESTRING << "Using Command: \"" << systemCmd << "\"" << endl;

            system(systemCmd.c_str());
            m_running = true;

            boost::filesystem::current_path(m_currentPath);

            cout << PIGA_DEBUG_PRESTRING << "======= Command Executed! =======" << endl;
        }
        else
        {
            cout << "Program \"" << getConfig(Name) << "\" in directory \"" << getConfig(Directory)
                 << "\" is not valid and cannot be started!" << endl;
        }
    }
    void GameHost::exit()
    {
        m_running = false;
    }
    bool GameHost::isValid()
    {
        return m_valid;
    }
    bool GameHost::isRunning()
    {
        return m_running;
    }
    void GameHost::invalidate(bool state)
    {
        m_valid = state;
    }
    void GameHost::setRunning(bool state)
    {
        m_running = state;
    }
    const std::string &GameHost::getConfig(GameHost::ConfigValue id)
    {
        return m_config[id];
    }
    void GameHost::setConfig(GameHost::ConfigValue id, const std::string &value)
    {
        m_config[id] = value;
    }
}
