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
            virtual void update();
            bool isActive() const;
        private:
            /**
             * @brief Sets the internal state of the input (on or off).
             * @param active Input on / off.
             *
             * This blocks reads from the isActive method until the new state has been set.
             */
            void setState(bool active);
            bool m_active = false;

            mutable boost::shared_mutex m_activeMutex;
    };
}

#endif
