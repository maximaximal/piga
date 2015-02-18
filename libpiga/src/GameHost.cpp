#include <piga/GameHost.hpp>
#include <sstream>
#include <yaml-cpp/yaml.h>
#include <boost/filesystem.hpp>
#include <iostream>
#include <piga/Definitions.hpp>
#include <piga/Host.hpp>

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
            setConfig(BackgroundImage, getConfig(Directory) + "/" + config["BackgroundImage"].as<std::string>());
        else
        {
            setConfig(BackgroundImage, "");
            cout << PIGA_DEBUG_PRESTRING << "The config.yml in \"" << directory << "\" has no BackgroundImage node!" << endl;
        }
        
        if(config["Logo"])
            setConfig(Logo, getConfig(Directory) +  "/" +config["Logo"].as<std::string>());
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
        
        if(config["KeyboardMappings"])
        {
            //Try to interpret the specific keyboard mappings for this game/application host.
            for(YAML::const_iterator mappingNode = config["KeyboardMappings"].begin(); mappingNode!= config["KeyboardMappings"].end(); ++mappingNode)
            {
                std::string mapping = (*mappingNode).as<std::string>();
                int playerID = atoi(mapping.substr(0, mapping.find(':')).c_str());
                std::string control = mapping.substr(mapping.find(':') + 1, mapping.find("->") - mapping.find(":") - 1);
                std::string mappedKey = mapping.substr(mapping.find("->") + 2);
                piga::GameControl gameControl;

                if(control == "UP")
                    gameControl = GameControl::UP;
                else if(control == "DOWN")
                    gameControl = GameControl::DOWN;
                else if(control == "LEFT")
                    gameControl = GameControl::LEFT;
                else if(control == "RIGHT")
                    gameControl = GameControl::RIGHT;
                else if(control == "ACTION")
                    gameControl = GameControl::ACTION;
                else if(control == "BUTTON1")
                    gameControl = GameControl::BUTTON1;
                else if(control == "BUTTON2")
                    gameControl = GameControl::BUTTON2;
                else if(control == "BUTTON3")
                    gameControl = GameControl::BUTTON3;
                else if(control == "BUTTON4")
                    gameControl = GameControl::BUTTON4;
                else if(control == "BUTTON5")
                    gameControl = GameControl::BUTTON5;
                else if(control == "BUTTON6")
                    gameControl = GameControl::BUTTON6;
                else
                {
                    cout << PIGA_DEBUG_PRESTRING << "[Keyboard Mapping Error in " << getConfig(Directory) << "]: The mapping \"" << control << "\" could not be interpreted!" << endl;
                }

                m_keyboardMappings[playerID][gameControl] = mappedKey;
                cout << PIGA_DEBUG_PRESTRING << "Added Mapping \"" << control << "\" (GameControl " << gameControl << ") -> \"" << mappedKey << "\" for player " << playerID << " in \"" << getConfig(Name) << "\"!" << endl;
            }
        }

        cout << PIGA_DEBUG_PRESTRING << "Loaded game \"" << getConfig(Name) << "\" from directory \"" << directory
             << "\"." << endl;
    }
    void GameHost::start()
    {
        if(isValid())
        {
            if(m_host)
            {
                if(m_host->gameIsRunning())
                {
                    return;
                }
            }
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
            
            if(m_host)
            {
                m_host->setCurrentGameHost(this);
            }
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
        if(m_host)
        {
            //Unset this gamehost from the host.
            m_host->setCurrentGameHost(nullptr);
        }
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
    void GameHost::sendGameEvent(const GameEvent &event)
    {
        if(event.type() == GameEvent::GameEventType::GameInput)
        {
            if(m_keyboardMappings.size() > 0)
            {
                if(m_keyboardMappings.count(event.playerID()) == 1)
                {
                    if(m_keyboardMappings[event.playerID()].count(event.gameInput.control()) == 1)
                    {
                        //Issue a xdotool keyboard command.
                        if(event.gameInput.state())
                            system(std::string("xdotool keydown " + m_keyboardMappings[event.playerID()][event.gameInput.control()] + ";").c_str());
                        else
                            system(std::string("xdotool keyup " + m_keyboardMappings[event.playerID()][event.gameInput.control()] + ";").c_str());
                    }
                }
            }
        }
    }
}
