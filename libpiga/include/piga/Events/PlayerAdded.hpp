#ifndef LIBPIGA_PIGA_EVENTS_PLAYERADDED_HPP_INCLUDED
#define LIBPIGA_PIGA_EVENTS_PLAYERADDED_HPP_INCLUDED

namespace piga
{
    namespace event
    {
        /**
         * @brief The PlayerAdded event is fired when a player has been added to the system.
         */
        class PlayerAdded
        {
            public:
                PlayerAdded(int id = 0, const char* name = "");
                ~PlayerAdded();

                void setName(const char* name);
                const char* getName() const;

                void setID(int id);
                int getID() const;

                PlayerAdded& operator=(const PlayerAdded &other);
            private:
                char m_name[255];
                int m_id;
        };
    }
}

#endif
