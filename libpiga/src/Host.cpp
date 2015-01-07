#include <piga/Host.hpp>
#include <piga/Status.hpp>
#include <piga/GameHost.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/lexical_cast.hpp>

namespace piga
{
    Host::Host()
    {

    }
    Host::~Host()
    {
        deleteSharedMemory();
    }
    void Host::init()
    {
        createSharedMemory();
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
