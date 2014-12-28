#include <pihud/FocusEvent.hpp>
#include <pihud/FocusManager.hpp>

namespace PiH
{
    FocusEvent::FocusEvent()
    {

    }
    FocusEvent::FocusEvent(DirectionEvent &dirEvent)
    {

    }
    FocusEvent::~FocusEvent()
    {

    }
    void FocusEvent::setHandled(bool handled) const
    {
        m_handled = handled;
    }
    bool FocusEvent::wasHandled() const
    {
        return m_handled;
    }
    bool FocusEvent::leftOrRight() const
    {
        if(direction == Direction::LEFT || Direction::RIGHT)
            return true;
        return false;
    }
    bool FocusEvent::upOrDown() const
    {
        if(direction == Direction::UP || Direction::DOWN)
            return true;
        return false;
    }
    void FocusEvent::focus(std::shared_ptr<Widget> focusedWidget) const
    {
        if(m_focusManager)
        {
			m_focusManager->setFocused(focusedWidget);
        }
        m_handled = true;
    }
    std::shared_ptr<FocusManager> FocusEvent::getFocusManager() const
    {
        return m_focusManager;
    }
    void FocusEvent::setFocusManager(std::shared_ptr<FocusManager> focusManager)
    {
        m_focusManager = focusManager;
    }
    bool FocusEvent::wasForced() const
    {
        return m_forced;
    }
}
