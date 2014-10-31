#ifndef LIBPIGA_PIGA_INPUTMETHOD_HPP_INCLUDED
#define LIBPIGA_PIGA_INPUTMETHOD_HPP_INCLUDED

#include <boost/thread/shared_mutex.hpp>

namespace piga
{
    /**
     * @brief The InputMethod class holds a single input method.
     *
     * Every engine/game has to implement the input methods it wants.
     *
     * Derived classes have to implement the wanted input method themselves!
     */
   	class InputMethod
    {
        public:
            /**
             * @brief Has to be implemented by the derived classes.
             *
             * The base update() function has to be called at the start of the derived function,
             * because this function resets the internal hasChanged flag.
             */
            virtual void update();
            bool isActive() const;
            /**
             * @brief Checks if the state has changed since the last update call.
             * @return
             */
            bool hasChanged();
        protected:
            /**
             * @brief Sets the internal state of the input (on or off).
             * @param active Input on / off.
             *
             * This blocks reads from the isActive method until the new state has been set.
             */
            void setState(bool active);
        private:
            void setChanged(bool changed);
            bool m_active = false;
            bool m_hasChanged = false;

            mutable boost::shared_mutex m_activeMutex;
            mutable boost::shared_mutex m_hasChangedMutex;
    };
}

#endif
