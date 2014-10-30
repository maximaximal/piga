#include <piga/Interface.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <cstddef>
#include <cassert>
#include <utility>

#include <piga/GameInput.hpp>
#include <piga/Host.hpp>
#include <piga/Definitions.hpp>
#include <iostream>

using std::cout;
using std::endl;

namespace piga
{
    Interface::Interface()
    {
        cout << PIGA_DEBUG_PRESTRING << "Trying to open the shared memory \"" << Host::getSharedMemoryName() << "\". ";
        boost::interprocess::managed_shared_memory segment(boost::interprocess::open_only, Host::getSharedMemoryName().c_str());
        cout << "Memory opened!" << endl;
        std::pair<GameInput*, boost::interprocess::managed_shared_memory::size_type> res;

        cout << PIGA_DEBUG_PRESTRING << "Opening the segment \"" << Host::getGameInputInstanceName() << "\".";
        res = segment.find<GameInput>(Host::getGameInputInstanceName().c_str());
        cout << " - Segment opened." << endl;

        if(res.second != 1)
        {
            //The object is not correct!
            throw(boost::interprocess::not_found_error);
        }
        else
        {
            cout << PIGA_DEBUG_PRESTRING << "Shared memory segment opened successfully! The link between PiGa and the application has been established." << endl;
        }

        externalGameInput = res.first;
    }
    Interface::~Interface()
    {
        cout << PIGA_DEBUG_PRESTRING << "Interface closed." << endl;
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
