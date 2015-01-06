#include <piga/Interface.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <cstddef>
#include <cassert>
#include <utility>

#include <piga/GameInput.hpp>
#include <piga/Host.hpp>
#include <piga/Definitions.hpp>
#include <piga/Status.hpp>
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
			using namespace boost::interprocess;
            cout << PIGA_DEBUG_PRESTRING << "Trying to open the shared memory \"" << Host::getInputSharedMemoryName() << "\"." << endl;
            shared_memory_object shm_input(open_only, Host::getInputSharedMemoryName(), read_write);
            cout << PIGA_DEBUG_PRESTRING << "Memory opened!" << endl;
            cout << PIGA_DEBUG_PRESTRING << "Memory opened - input polling should be working." << endl;
        }
    }
    Interface::~Interface()
    {
        if(m_selfhosted)
        {
            delete externalGameInput;
            cout << PIGA_DEBUG_PRESTRING << "Selfhosted GameInput instance deleted." << endl;
        }
        else
        {
            using namespace boost::interprocess;
            managed_shared_memory shm_status(open_only, piga::Host::getStatusSharedMemoryName());

            std::pair<piga::Status*, std::size_t> p =
                    shm_status.find<piga::Status>("Status");

            piga::Status *status = p.first;

            status->setRunning(false);
            cout << PIGA_DEBUG_PRESTRING << "Status set to not running." << endl;
        }
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
        if(isSelfhosted())
			return externalGameInput->pollEvent(event);
        else
        {
            if(events.size() > 0)
            {
                event = events.front();
                events.pop_front();
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    bool Interface::isSelfhosted()
    {
        return m_selfhosted;
    }
    void Interface::update()
    {
        if(isSelfhosted())
        {
            externalGameInput->update();
        }
        else
        {
			using namespace boost::interprocess;
            managed_shared_memory shm(open_only, piga::Host::getInputSharedMemoryName());

			std::pair<PlayerInputStruct*, std::size_t> p =
					shm.find<PlayerInputStruct>("PlayerInput");

            GameEvent e;

            if(m_playerInputs.size() != p.second)
            {
                m_playerInputs.resize(p.second);
            }

            for(std::size_t i = 0; i < p.second; ++i)
            {
                while(p.first[i].pollEvents(m_playerInputs[i], e))
                {
                    events.push_back(e);
                }
            }
        }
    }
    void Interface::logToStatus(const std::string &message)
    {
        if(m_selfhosted)
        {
            using namespace boost::interprocess;
            managed_shared_memory shm(open_only, piga::Host::getStatusSharedMemoryName());

            std::pair<piga::Status*, std::size_t> p =
                    shm.find<piga::Status>("Status");

            piga::Status *status = p.first;
        }
    }
}
