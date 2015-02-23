#include <pihud/FocusManager.hpp>

namespace PiH
{
    FocusManager::FocusManager()
    {

    }
    FocusManager::~FocusManager()
    {

    }
    void FocusManager::setFocused(std::shared_ptr<Widget> widget, int playerID)
    {
        if(m_focused[playerID])
        {
            m_focused[playerID]->m_focused = false;
            m_focused[playerID]->focusLost(playerID);
        }
        
        m_focused[playerID] = widget;
        widget->m_focused = true;
        widget->focusGained(playerID);
    }
    std::shared_ptr<Widget> FocusManager::getFocused(int playerID)
    {
        return m_focused[playerID];
    }
    bool FocusManager::isFocusedByPlayer(Widget *widget, int playerID)
    {
        if(m_focused.count(playerID) > 0)
        {
            if(m_focused[playerID].get() == widget)
            {
                return true;
            }
        }
        return false;
    }
}
