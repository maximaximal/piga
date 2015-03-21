#include <iostream>
#include <string>
#include <cstring>

#include <piga/Events/PlayerRemoved.hpp>
#include <piga/Definitions.hpp>

using std::cout;
using std::endl;

namespace piga
{
    namespace event
    {
        PlayerRemoved::PlayerRemoved(int id, const char *name)
            : m_id(id)
        {
            setName(name);
        }
        PlayerRemoved::~PlayerRemoved()
        {

        }
        void PlayerRemoved::setName(const char *name)
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
        const char *PlayerRemoved::getName()
        {
            return m_name;
        }
        void PlayerRemoved::setID(int id)
        {
            m_id = id;
        }
        int PlayerRemoved::getID()
        {
            return m_id;
        }
    }
}
