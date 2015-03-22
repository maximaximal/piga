#include <iostream>
#include <string>
#include <cstring>

#include <piga/Events/PlayerAdded.hpp>
#include <piga/Definitions.hpp>

using std::cout;
using std::endl;

namespace piga
{
    namespace event
    {
        PlayerAdded::PlayerAdded(int id, const char *name)
            : m_id(id)
        {
            setName(name);
        }
        PlayerAdded::~PlayerAdded()
        {

        }
        void PlayerAdded::setName(const char *name)
        {
            if(strlen(name) > 255)
            {
                cout << PIGA_DEBUG_PRESTRING << "Username was longer than 255 characters! Truncated the name to fit the maximum size." << endl;
                strncpy(m_name, name, 254);
            }
            else
            {
                strcpy(m_name, name);
            }
        }
        const char *PlayerAdded::getName() const
        {
            return m_name;
        }
        void PlayerAdded::setID(int id)
        {
            m_id = id;
        }
        int PlayerAdded::getID() const
        {
            return m_id;
        }
        PlayerAdded& PlayerAdded::operator=(const PlayerAdded &other)
        {
            setID(other.getID());
            setName(other.getName());
            return *this;
        }
    }
}
