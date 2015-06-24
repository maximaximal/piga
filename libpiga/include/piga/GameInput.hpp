#ifndef LIBPIGA_PIGA_GAMEINPUT_HPP_INCLUDED
#define LIBPIGA_PIGA_GAMEINPUT_HPP_INCLUDED

#include <map>
#include <memory>
#include <deque>

#include <piga/PlayerInput.hpp>
#include <piga/GameEvent.hpp>
#include <boost/thread/shared_mutex.hpp>

namespace piga 
{
    /**
     * @brief Manages the whole input of a game. 
     */
    class GameInput 
    {
        public:
            GameInput();
            virtual ~GameInput();
            
            void update();
            
            int addPlayerInput(std::shared_ptr<PlayerInput> playerInput);
            void pushGameEvent(const GameEvent &e);

            int getPlayerCount();
            const PlayerInput& getPlayerInput(int id);

            bool pollEvent(GameEvent &gameEvent);
        private:
            std::map<int, std::shared_ptr<PlayerInput> > m_playerInputs;
            std::deque<GameEvent> m_gameEvents;

            boost::shared_mutex m_eventMutex;
            
            int m_playerInputIdCounter = 0;
    };
}

#endif
