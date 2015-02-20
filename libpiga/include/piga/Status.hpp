#ifndef LIBPIGA_PIGA_STATUS_HPP_INCLUDED
#define LIBPIGA_PIGA_STATUS_HPP_INCLUDED

#include <string>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>

namespace piga
{
    /**
     * @brief The Status class contains information about the status of a game instance.
     */
    class Status
    {
        public:
            /**
             * @brief Create the piga::Status class.
             * 
             * @param running Defines if a game/app is already running when this instance is beeing constructed. 
             */
            Status(bool running);
            virtual ~Status();
            /**
             * @brief Checks if a game/app is running.
             * 
             * @return True if a game/app is running, false otherwise. 
             */
            bool isRunning();
            /**
             * @brief Sets the running state of the game/app the piga::Status instance. 
             * 
             * @param state The state to be set as isRunning state. 
             */
            void setRunning(bool state);
            
            /**
             * @brief Returns the credits left.
             * 
             * @return Left credits.
             */
            int getCreditCount();
            /**
             * @brief Sets the remaining credits.
             * 
             * @param credits The remaining credits.
             */
            void setCreditCount(int credits);
            /**
             * @brief Adds the specified amount to the remaining credits.
             * 
             * @param amount The amount to be added to the remaining credits.
             * @return The remaining credits.
             */
            int addCredits(int amount = 1);
            /**
             * @brief Removes the specified amount from the remaining credits.
             * 
             * @param amount The amount to be removed from the remaining credits. Defaults to 1.
             * @return The remaining tickets.
             */
            int removeCredits(int amount = 1);
        private:
            bool m_running;
            int m_creditCount;
            boost::interprocess::interprocess_mutex m_runningMutex;
            boost::interprocess::interprocess_mutex m_creditsMutex;
    };
}

#endif
