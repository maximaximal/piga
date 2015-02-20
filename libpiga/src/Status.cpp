#include <piga/Status.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

namespace ip = boost::interprocess;

namespace piga
{
    Status::Status(bool running)
        :  m_running(running)
    {

    }
    Status::~Status()
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
    int Status::getCreditCount()
    {
        ip::scoped_lock<ip::interprocess_mutex> lock(m_creditsMutex);
        return m_creditCount;
    }
    void Status::setCreditCount(int credits)
    {
        ip::scoped_lock<ip::interprocess_mutex> lock(m_creditsMutex);
        m_creditCount = credits;
    }
    int Status::addCredits(int amount)
    {
        ip::scoped_lock<ip::interprocess_mutex> lock(m_creditsMutex);
        m_creditCount += amount;
        return m_creditCount;
    }
    int Status::removeCredits(int amount)
    {
        return addCredits(-amount);
    }
}
