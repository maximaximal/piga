#include <piga/Host.hpp>
#include <piga/Status.hpp>
#include <piga/GameHost.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/lexical_cast.hpp>

#include <yaml-cpp/yaml.h>

namespace piga
{
    Host::Host(const std::string &configFile)
        : m_configFile(configFile)
    {

    }
    Host::~Host()
    {
        m_sharedLibs.clear();
        deleteSharedMemory();
    }
    void Host::init()
    {
        m_sharedLibs.clear();

        createSharedMemory();

        YAML::Node doc = YAML::LoadAllFromFile(m_configFile).front();
        if(doc["hosts"])
        {
            for(YAML::const_iterator it = doc["hosts"].begin(); it != doc["hosts"].end(); ++it)
            {
                std::shared_ptr<SharedLibWrapper> sharedLib = std::make_shared<SharedLibWrapper>((*it).as<std::string>());
                sharedLib->init(m_playerCount);
                m_sharedLibs.push_back(sharedLib);
            }
        }
    }
    void Host::applyFromGameInput(GameInput *gameInput)
    {
        using namespace boost::interprocess;
        managed_shared_memory shm(open_only, getInputSharedMemoryName());

        std::pair<PlayerInputStruct*, std::size_t> p =
                shm.find<PlayerInputStruct>("PlayerInput");

        GameEvent event;
        while(gameInput->pollEvent(event))
        {
            p.first[event.playerID()].fromGameEvent(event);
        }
    }
    void Host::setInput(unsigned int playerID, GameControl control, bool state)
    {
        using namespace boost::interprocess;
        managed_shared_memory shm(open_only, getInputSharedMemoryName());

        std::pair<PlayerInputStruct*, std::size_t> p =
                shm.find<PlayerInputStruct>("PlayerInput");

        p.first[playerID].fromGameEvent(control, state);
    }
    void Host::setCurrentGameHost(std::shared_ptr<GameHost> gameHost)
    {
        m_currentGameHost = gameHost;
        if(m_currentGameHost->isRunning())
        {
            using namespace boost::interprocess;
            managed_shared_memory shm(open_only, getStatusSharedMemoryName());

            std::pair<Status*, std::size_t> p =
                    shm.find<Status>("Status");

            Status *status = p.first;

            status->setRunning(true);
        }
    }
    bool Host::gameIsRunning()
    {
        using namespace boost::interprocess;
        managed_shared_memory shm(open_only, getStatusSharedMemoryName());

        std::pair<Status*, std::size_t> p =
                shm.find<Status>("Status");

        Status *status = p.first;

        if(m_currentGameHost)
        {
            if(m_currentGameHost->isRunning())
            {
                if(!status->isRunning())
                {
                    m_currentGameHost->setRunning(false);
                }
            }
            else
            {
                if(status->isRunning())
                {
                    m_currentGameHost->setRunning(true);
                }
            }
        }
        return status->isRunning();
    }
    void Host::update(float frametime)
    {
        for(std::size_t i = 0; i < m_playerCount; ++i)
        {
            for(unsigned int control = GameControl::UP; control < GameControl::_COUNT; ++control)
            {
                for(auto sharedLibWrapper : m_sharedLibs)
                {
                    sharedLibWrapper->query(this, i, static_cast<GameControl>(control));
                }
            }
        }
    }
    const char *Host::getInputSharedMemoryName()
    {
        return "PiGa_GameInterface";
    }
    const char *Host::getStatusSharedMemoryName()
    {
        return "PiGa_GameStatus";
    }
    void Host::createSharedMemory()
    {
        using namespace boost::interprocess;

        deleteSharedMemory();

        managed_shared_memory shm_input(create_only,
                                  getInputSharedMemoryName(),
                                  1024);

        for(std::size_t i = 1; i < m_playerCount; ++i)
        {
            shm_input.construct<PlayerInputStruct>("PlayerInput")[m_playerCount]();
        }

        managed_shared_memory shm_status(create_only,
                                  getStatusSharedMemoryName(),
                                  1024);

        shm_status.construct<Status>("Status")[1](false);
    }
    void Host::deleteSharedMemory()
    {
        boost::interprocess::shared_memory_object::remove(getInputSharedMemoryName());
        boost::interprocess::shared_memory_object::remove(getStatusSharedMemoryName());
    }
}
