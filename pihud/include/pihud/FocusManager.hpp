#pragma once

#include <memory>

#include <pihud/Widget.hpp>

namespace PiH
{
    /**
     * @brief The FocusManager class manages the focus of widgets in the GUI.
     */
    class FocusManager
    {
        public:
            FocusManager();
            virtual ~FocusManager();

            void setFocused(std::shared_ptr<Widget> widget);
        private:
            std::shared_ptr<Widget> m_focusedWidget;
    };
}
