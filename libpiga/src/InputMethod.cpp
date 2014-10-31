#include <piga/InputMethod.hpp>

#include <boost/thread/locks.hpp>

namespace piga
{
    void InputMethod::update()
    {
        setChanged(false);
    }
    bool InputMethod::isActive() const
    {
        boost::shared_lock<boost::shared_mutex> lock(m_activeMutex);
        return m_active;
    }
    bool InputMethod::hasChanged()
    {
        boost::shared_lock<boost::shared_mutex> lock(m_hasChangedMutex);
        if(m_hasChanged)
            return true;
        return false;
    }
    void InputMethod::setState(bool active)
    {
        boost::upgrade_lock<boost::shared_mutex> lock(m_activeMutex);
        boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);

        if(m_active != active)
        {
            m_active = active;
            setChanged(true);
        }
    }
    void InputMethod::setChanged(bool changed)
    {
        boost::upgrade_lock<boost::shared_mutex> lock(m_hasChangedMutex);
        boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);

        m_hasChanged = changed;
    }
}
