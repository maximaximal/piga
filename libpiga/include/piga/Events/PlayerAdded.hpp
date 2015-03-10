#ifndef LIBPIGA_PIGA_EVENTS_PLAYERADDED_HPP_INCLUDED
#define LIBPIGA_PIGA_EVENTS_PLAYERADDED_HPP_INCLUDED

namespace piga
{
    namespace event
    {
        class PlayerAdded
        {
            public:
                PlayerAdded();
                virtual ~PlayerAdded();

                const char* getName();
                int getID();
            private:
                char m_name[255];
                int m_id;
        };
    }
}

#endif
