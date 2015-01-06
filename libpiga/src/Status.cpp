#include <piga/Status.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

namespace ip = boost::interprocess;

namespace piga
{
    Status::Status(bool running)
        :  m_running(running)
    {

    }
    bool Status::isRunning()
    {
        ip::scoped_lock<ip::interprocess_mutex> lock(m_runningMutex);
        return m_running;
    }
    void Status::setRunning(bool state)
    {
        ip::scoped_lock<ip::interprocess_mutex> lock(m_runningMutex);
        m_running = state;
    }
}
