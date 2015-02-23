#pragma once

#include <memory>
#include <map>

#include <pihud/Widget.hpp>

namespace PiH
{
    /**
     * @brief The FocusManager class manages the focus of widgets in the GUI.
     * 
     * The focus manager maanges the focus of all players individually.
     */
    class FocusManager
    {
        public:
            FocusManager();
            virtual ~FocusManager();

            void setFocused(std::shared_ptr<Widget> widget, int playerID = -1);
            std::shared_ptr<Widget> getFocused(int playerID = -1);
            
            bool isFocusedByPlayer(Widget *widget, int playerID);
        private:
            std::map<int, std::shared_ptr<Widget>> m_focused;
    };
}
