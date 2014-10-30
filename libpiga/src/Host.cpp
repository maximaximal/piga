#include <piga/Host.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <cstddef>
#include <cassert>
#include <utility>

namespace piga
{
    Host::Host()
    {
        createSharedMemory();
    }
    Host::~Host()
    {
        deleteSharedMemory();
    }
    void Host::update()
    {
        m_gameInput->update();
    }
    GameInput *Host::getGameInput()
    {
        return m_gameInput;
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
        boost::interprocess::managed_shared_memory segment(boost::interprocess::create_only, getSharedMemoryName().c_str(), sizeof(GameInput));
        m_gameInput = segment.construct<GameInput>(getGameInputInstanceName().c_str())();
    }
    void Host::deleteSharedMemory()
    {
        boost::interprocess::managed_shared_memory segment(boost::interprocess::open_only, Host::getSharedMemoryName().c_str());

        segment.destroy<GameInput>(getGameInputInstanceName().c_str());

        boost::interprocess::shared_memory_object::remove(getSharedMemoryName().c_str());
    }
}
