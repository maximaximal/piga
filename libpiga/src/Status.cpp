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
    void Status::log(const std::string &message)
    {
        boost::interprocess::string msg;
        msg = message.c_str();
        m_log.push_back(msg);
    }
    void Status::pushEvent(const GameEvent &event)
    {
        m_events.push_back(event);
    }
    bool Status::popEvent(GameEvent *e)
    {
        bool events = hasEvents();
        if(events)
        {
            *e = m_events.front();
            m_events.pop_front();
        }
        return events;
    }
    bool Status::hasEvents()
    {
        if(m_events.size() > 0)
            return true;
        return false;
    }
    bool Status::hasLogMessages()
    {
        if(m_log.size() > 0)
            return true;
        return false;
    }
    const char *Status::getTopLogMessage()
    {
        boost::interprocess::string msg = m_log.front();
        return msg.c_str();
    }
    bool Status::popLogMessage(std::string *msg)
    {
        bool hasLogs = hasLogMessages();
        if(hasLogs)
        {
            *msg = m_log.front().c_str();
            m_log.pop_front();
        }
        return hasLogs;
    }
}
