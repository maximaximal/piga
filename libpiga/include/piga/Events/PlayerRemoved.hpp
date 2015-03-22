#ifndef LIBPIGA_PIGA_EVENTS_PLAYERREMOVED_HPP_INCLUDED
#define LIBPIGA_PIGA_EVENTS_PLAYERREMOVED_HPP_INCLUDED

namespace piga
{
    namespace event
    {
        /**
         * @brief The PlayerRemoved event is fired when a player is removed from the system.
         */
        class PlayerRemoved
        {
            public:
                PlayerRemoved(int id = 0, const char* name = "");
                ~PlayerRemoved();

                void setName(const char* name);
                const char* getName() const;

                void setID(int id);
                int getID() const;

                PlayerRemoved& operator=(const PlayerRemoved &other);
            private:
                char m_name[255];
                int m_id;
        };
    }
}

#endif
