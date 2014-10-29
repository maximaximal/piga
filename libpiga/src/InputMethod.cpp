#include <piga/InputMethod.hpp>

#include <boost/thread/locks.hpp>

namespace piga
{
    void InputMethod::update()
    {
		//Not set (implemented by child class)
    }
    bool InputMethod::isActive() const
    {
        boost::shared_lock<boost::shared_mutex> lock(m_activeMutex);
        return m_active;
    }
    void InputMethod::setState(bool active)
    {
        boost::upgrade_lock<boost::shared_mutex> lock(m_activeMutex);
        boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);

        m_active = active;
    }
}
