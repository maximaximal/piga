#include <pihud/FocusManager.hpp>

namespace PiH
{
    void FocusManager::setFocused(std::shared_ptr<Widget> widget)
    {
		m_focusedWidget->m_focused = false;
        m_focusedWidget = widget;
		m_focusedWidget->m_focused = true;
    }
}
