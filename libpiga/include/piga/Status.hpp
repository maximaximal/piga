#ifndef LIBPIGA_PIGA_STATUS_HPP_INCLUDED
#define LIBPIGA_PIGA_STATUS_HPP_INCLUDED

#include <string>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/containers/deque.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include <piga/GameEvent.hpp>

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
            /**
             * @brief Adds a message to the internal log buffer.
             *
             * The log is read by the host application and will be displayed as configured.
             * @param message The message to send.
             */
            void log(const std::string &message);
            /**
             * @brief Pushes an event to the internal event buffer. This function should only be used by the host program.
             *
             * The game/application can then read events with the popEvent() function.
             *
             * @param event The event to push.
             */
            void pushEvent(const GameEvent &event);
            /**
             * @brief Reads the newest event into the specified event ptr and pops the event from the internal buffer afterwards.
             * @param e The event to be overwritten with the new one.
             * @return True if an event happened, false otherwise. (For while() loops).
             */
            bool popEvent(GameEvent *e);
            /**
             * @brief Checks if events happened.
             * @return True if the internal event buffer contains events, false otherwise.
             */
            bool hasEvents();
            /**
             * @brief Checks if there are log messages.
             * @return True if the internal buffer contains log messages, false otherwise.
             */
            bool hasLogMessages();
            /**
             * @brief Returns the newest log message without modifying the internal buffer.
             * @return The newest log message.
             */
            const char* getTopLogMessage();
            /**
             * @brief Reads the newest log message in the provided string and pops the message from the internal buffer afterwards.
             * @param msg The string to write the new log message into.
             * @return True if there was a message, false otherwise.
             */
            bool popLogMessage(std::string *msg);
        private:
            bool m_running;
            int m_creditCount;
            boost::interprocess::interprocess_mutex m_runningMutex;
            boost::interprocess::interprocess_mutex m_creditsMutex;

            boost::interprocess::deque<boost::interprocess::string> m_log;
            boost::interprocess::deque<GameEvent> m_events;
    };
}

#endif
