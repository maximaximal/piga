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
    Interface::Interface(bool selfhosted)
    {
        m_selfhosted = selfhosted;
        if(selfhosted)
        {
            cout << PIGA_DEBUG_PRESTRING << "Setting up a selfhosted piga interface. This interface is hosted by the application itself and does not use shared memory." << endl;
            externalGameInput = new GameInput();
        }
        else
        {
            cout << PIGA_DEBUG_PRESTRING << "Trying to open the shared memory \"" << Host::getSharedMemoryName() << "\"." << endl;
            boost::interprocess::managed_shared_memory segment(boost::interprocess::open_only, Host::getSharedMemoryName().c_str());
            cout << "Memory opened!" << endl;
            std::pair<GameInput*, boost::interprocess::managed_shared_memory::size_type> res;

            cout << PIGA_DEBUG_PRESTRING << "Opening the segment \"" << Host::getGameInputInstanceName() << "\"." << endl;
            res = segment.find<GameInput>(Host::getGameInputInstanceName().c_str());
            cout << "Segment opened." << endl;

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
    }
    Interface::~Interface()
    {
        cout << PIGA_DEBUG_PRESTRING << "Interface closed." << endl;
        if(m_selfhosted)
        {
            delete externalGameInput;
            cout << PIGA_DEBUG_PRESTRING << "Selfhosted GameInput instance deleted." << endl;
        }
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
    int Interface::addPlayerInput(std::shared_ptr<PlayerInput> playerInput)
    {
        if(isSelfhosted())
        {
            return externalGameInput->addPlayerInput(playerInput);
        }
        throw(std::out_of_range("Player inputs can only be added through the interface, if the interface is selfhosted!"));
    }
    bool Interface::pollEvent(GameEvent &event)
    {
        return externalGameInput->pollEvent(event);
    }
    bool Interface::isSelfhosted()
    {
        return m_selfhosted;
    }
}
