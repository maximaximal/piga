#pragma once

#include <memory>
#include <piga/GameEvent.hpp>
#include <pihud/Direction.hpp>

namespace PiH
{
    class FocusManager;
    class Widget;

    /**
     * @brief The FocusEvent class passes focusevents down the event-tree.
     *
     * If a widget handled the focus event and applied it, the event should not be passed around
     * further. Please include a check if the focus event was already handled before you try to handle
     * it in your own code!
     */
    class FocusEvent
    {
        public:
            FocusEvent();
            FocusEvent(const piga::GameEvent &gameEvent);
            virtual ~FocusEvent();

            void setHandled(bool handled = true) const;
            bool wasHandled() const;

			bool leftOrRight() const;
            bool upOrDown() const;
            
            Direction direction;

            void focus(std::shared_ptr<Widget> focusedWidget) const;
            
            FocusEvent& operator=(const FocusEvent &other);

            std::shared_ptr<FocusManager> getFocusManager() const;
            void setFocusManager(std::shared_ptr<FocusManager> focusManager);

            /**
             * @brief Checks if the focus event was forced by a specific action of the user.
             * @return True, if the event was forced.
             *
             * If a focus event was forced, the widget handling the event should not try to
             * act differently (for example, only handle the direction events and not focus events)
             * and instead only execute the behavior for a focus event.
             *
             * A line editor for example should not set the focus event to handled, but instead do nothong.
             */
            bool wasForced() const;
        private:
            mutable bool m_handled = false;
            mutable std::shared_ptr<FocusManager> m_focusManager;
            bool m_forced = false;
    };
}
