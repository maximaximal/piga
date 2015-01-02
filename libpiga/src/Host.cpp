#include <piga/Host.hpp>
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
        managed_shared_memory shm(open_only, getSharedMemoryName().c_str());

        std::pair<PlayerInputStruct*, std::size_t> p =
                shm.find<PlayerInputStruct>("PlayerInput");

        GameEvent event;
        while(gameInput->pollEvent(event))
        {
            p.first[event.getPlayerID()].fromGameEvent(event);
        }
    }
    void Host::setInput(unsigned int playerID, GameControl control, bool state)
    {
        using namespace boost::interprocess;
        managed_shared_memory shm(open_only, getSharedMemoryName().c_str());

        std::pair<PlayerInputStruct*, std::size_t> p =
                shm.find<PlayerInputStruct>("PlayerInput");

        p.first[playerID].fromGameEvent(control, state);
    }
    void Host::setCurrentGameHost(std::shared_ptr<GameHost> gameHost)
    {
        m_currentGameHost = gameHost;
    }
    std::string Host::getSharedMemoryName()
    {
        return "PiGa_GameInterface";
    }
    std::string Host::getGameInputInstanceName()
    {
        return "GameInputInstance";
    }
    void Host::createSharedMemory()
    {
        using namespace boost::interprocess;

        managed_shared_memory shm(open_or_create,
                                  getSharedMemoryName().c_str(),
                                  1024);

        for(std::size_t i = 1; i < m_playerCount; ++i)
        {
			shm.construct<PlayerInputStruct>("PlayerInput")[m_playerCount]();
        }
    }
    void Host::deleteSharedMemory()
    {
        boost::interprocess::shared_memory_object::remove(getSharedMemoryName().c_str());
    }
}
