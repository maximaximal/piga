#ifndef LIBPIGA_PIGA_PLAYERINPUT_HPP_INCLUDED
#define LIBPIGA_PIGA_PLAYERINPUT_HPP_INCLUDED

#include <map>
#include <deque>
#include <piga/GameControl.hpp>
#include <piga/InputMethod.hpp>
#include <piga/GameEvent.hpp>

namespace piga 
{
    class GameInput;

    /**
     * @brief The PlayerInputStruct struct provides a interface format for shred memory.
     *
     * The direction maximum is 100000, minimum is 0.
     */
    struct PlayerInputStruct
    {
        int up = 0;
        int down = 0;
        int left = 0;
        int right = 0;
        bool action = false;
    	bool button1 = false;
        bool button2 = false;
        bool button3 = false;
        bool button4 = false;
        bool button5 = false;
        bool button6 = false;
        void fromGameEvent(GameEvent &e);
        void fromGameEvent(const GameControl &control, bool state);
        bool pollEvents(PlayerInputStruct &oldInputs, GameEvent &e);
    };

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
            std::deque<GameEvent> m_gameEvents;
            int m_playerID;
    };
}

#endif
