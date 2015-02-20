#ifndef LIBPIGA_PIGA_STATUS_HPP_INCLUDED
#define LIBPIGA_PIGA_STATUS_HPP_INCLUDED

#include <string>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>

namespace piga
{
    /**
     * @brief The Status class contains information about the status of a game instance.
     */
    class Status
    {
        public:
            Status(bool running);
            bool isRunning();
            void setRunning(bool state);
            
            int getCreditCount();
            void setCreditCount(int credits);
            int addCredit();
        private:
            bool m_running;
            int m_creditCount;
            boost::interprocess::interprocess_mutex m_runningMutex;
            boost::interprocess::interprocess_mutex m_creditsMutex;
    };
}

#endif
