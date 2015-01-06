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
        private:
            bool m_running;
            boost::interprocess::interprocess_mutex m_runningMutex;
    };
}

#endif
