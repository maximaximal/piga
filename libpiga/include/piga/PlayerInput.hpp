#ifndef LIBPIGA_PIGA_PLAYERINPUT_HPP_INCLUDED
#define LIBPIGA_PIGA_PLAYERINPUT_HPP_INCLUDED

#include <map>
#include <queue>
#include <piga/GameControl.hpp>
#include <piga/InputMethod.hpp>
#include <piga/GameEvent.hpp>

namespace piga 
{
    class GameInput;

    /**
     * @brief The PlayerInput class holds the inputs of a player.
     *
     * The update method cannot be called by the program, it has to be called by the GameInput class.
	 */
    class PlayerInput 
    {
		friend class GameInput;

        public:
            PlayerInput();
            virtual ~PlayerInput();

            bool getInput(GameControl control) const;
            bool pollEvent(GameEvent &gameEvent);
            void setPlayerID(int playerID);
            int setInputMethod(InputMethod *method, GameControl control);
        protected:
            void update();

            void pushGameEvent(const GameEvent &gameEvent);
        private:
            std::map<GameControl, InputMethod*> m_inputMethods;
            std::queue<GameEvent> m_gameEvents;
            int m_playerID;
    };
}

#endif
