#include <piga/Interface.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <cstddef>
#include <cassert>
#include <utility>

#include <piga/GameInput.hpp>
#include <piga/Host.hpp>

namespace piga
{
    Interface::Interface()
    {
        boost::interprocess::managed_shared_memory segment(boost::interprocess::open_only, Host::getSharedMemoryName().c_str());

        std::pair<GameInput*, boost::interprocess::managed_shared_memory::size_type> res;

        res = segment.find<GameInput>(Host::getGameInputInstanceName().c_str());

        if(res.second != 1)
        {
            //The object is not correct!
            throw(boost::interprocess::not_found_error);
        }

        externalGameInput = res.first;
    }
    Interface::~Interface()
    {

    }
    int Interface::getPlayerCount()
    {
        if(gameInputSet())
        {
            return externalGameInput->getPlayerCount();
        }
        return 0;
    }
    const PlayerInput &Interface::getPlayerInput(int id)
    {
        if(gameInputSet())
        {
            return externalGameInput->getPlayerInput(id);
        }
        throw(boost::interprocess::not_found_error);
    }
    bool Interface::gameInputSet()
    {
        if(externalGameInput != nullptr)
        {
            return true;
        }
        return false;
    }
}
