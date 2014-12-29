#include <piga/GameHost.hpp>
#include <sstream>
#include <easylogging++.h>
#include <yaml-cpp/yaml.h>

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
        LOG(INFO) << "Loading game from \"" << directory << "\".";

        YAML::Node config;

        try {
			config = YAML::LoadAllFromFile(directory + "/config.yml").front();
        }
        catch(std::exception &e) {
            LOG(FATAL) << "The config.yml in \"" << directory << "\" could not be loaded!";
            return;
        }

        if(config["Name"])
            setConfig(Name, config["Name"].as<std::string>());
        else
        {
            setConfig(Name, "Unnamed");
            LOG(WARNING) << "The config.yml in \"" << directory << "\" has no Name node!";
        }

        if(config["Parameters"])
            setConfig(Parameters, config["Parameters"].as<std::string>());
        else
        {
            setConfig(Parameters, "");
            LOG(WARNING) << "The config.yml in \"" << directory << "\" has no Parameters node!";
        }

        if(config["ProgramPath"])
            setConfig(ProgramPath, config["ProgramPath"].as<std::string>());
        else
        {
            setConfig(ProgramPath, "Client");
            LOG(WARNING) << "The config.yml in \"" << directory << "\" has no ProgramPath node!";
        }

        LOG(INFO) << "Loaded game \"" << getConfig(Name) << "\" from directory \"" << directory
                  << "\".";
    }
    void GameHost::start()
    {
        if(isValid())
        {
			LOG(INFO) << "Starting program \"" << getConfig(Name) << "\"";

			std::stringstream command;
			command << getConfig(Directory) << "/";
			command << getConfig(ProgramPath);
			command << " ";
			command << getConfig(Parameters);

			std::string systemCmd = command.str();

			LOG(INFO) << "Using Command: \"" << systemCmd << "\"";

			system(systemCmd.c_str());

			LOG(INFO) << "======= Command Executed! =======";
        }
        else
        {
            LOG(WARNING) << "Program \"" << getConfig(Name) << "\" in directory \"" << getConfig(Directory)
                      << "\" is not valid and cannot be started!";
        }
    }
    void GameHost::exit()
    {

    }
    bool GameHost::isValid()
    {
        return m_valid;
    }
    void GameHost::invalidate(bool state)
    {
        m_valid = state;
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
