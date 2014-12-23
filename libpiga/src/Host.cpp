#include <piga/Host.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

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
        shared_memory_object object(open_only,
                                    getSharedMemoryName().c_str(),
                                    read_write);


        GameEvent event;
        while(gameInput->pollEvent(event))
        {
            mapped_region region(object, read_write,
                                 event.getPlayerID() + static_cast<unsigned int>(event.getControl()),
                                 1);

            std::memset(region.get_address(),
                        event, 1);
        }
    }
    void Host::setInput(unsigned int playerID, GameControl control, bool state)
    {
        using namespace boost::interprocess;
        shared_memory_object object(open_only,
                                    getSharedMemoryName().c_str(),
                                    read_write);

        mapped_region region(object, read_write, playerID + static_cast<unsigned int>(control), 1);

        std::memset(region.get_address(),
                    state, 1);
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

        shared_memory_object object(open_or_create,
                                    getSharedMemoryName().c_str(),
                                    read_write);

        unsigned int inputSize = m_playerCount * (unsigned int) ((m_buttonCount / 8.f) + 0.5);

        object.truncate(inputSize);

        mapped_region region(object, read_write);

        std::memset(region.get_address(), region.get_size(), 0);
    }
    void Host::deleteSharedMemory()
    {
        boost::interprocess::shared_memory_object::remove(getSharedMemoryName().c_str());
    }
}
