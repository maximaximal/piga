#ifndef LIBPIGA_PIGA_PLAYERINPUT_HPP_INCLUDED
#define LIBPIGA_PIGA_PLAYERINPUT_HPP_INCLUDED

#include <map>
#include <deque>
#include <piga/GameControl.hpp>
#include <piga/InputMethod.hpp>
#include <piga/GameEvent.hpp>

#include <boost/interprocess/detail/atomic.hpp>

namespace piga 
{
    class GameInput;

    /**
     * @brief The PlayerInputStruct struct provides a interface format for shred memory.
     *
     * The direction maximum is 100000, minimum is 0.
     */
    class PlayerInputStruct
    {
        public:
            PlayerInputStruct();
            virtual ~PlayerInputStruct();

            void fromGameEvent(GameEvent &e);
            void fromGameEvent(const GameControl &control, bool state);
            bool pollEvents(PlayerInputStruct &oldInputs, GameEvent &e);

            void setUp(int val);
            void setDown(int val);
            void setLeft(int val);
            void setRight(int val);
            void setAction(bool state);
            void setButton1(bool state);
            void setButton2(bool state);
            void setButton3(bool state);
            void setButton4(bool state);
            void setButton5(bool state);
            void setButton6(bool state);

            int up();
            int down();
            int left();
            int right();
            bool action();
            bool button1();
            bool button2();
            bool button3();
            bool button4();
            bool button5();
            bool button6();

            void invertUp();
            void invertDown();
            void invertLeft();
            void invertRight();
            void invertAction();
            void invertButton1();
            void invertButton2();
            void invertButton3();
            void invertButton4();
            void invertButton5();
            void invertButton6();
        private:
            void setLikeBoolean(volatile boost::uint32_t *number, bool state);
            bool getLikeBoolean(volatile boost::uint32_t *number);
            volatile boost::uint32_t m_up = 0;
            volatile boost::uint32_t m_down = 0;
            volatile boost::uint32_t m_left = 0;
            volatile boost::uint32_t m_right = 0;
            volatile boost::uint32_t m_action = 0;
            volatile boost::uint32_t m_button1 = 0;
            volatile boost::uint32_t m_button2 = 0;
            volatile boost::uint32_t m_button3 = 0;
            volatile boost::uint32_t m_button4 = 0;
            volatile boost::uint32_t m_button5 = 0;
            volatile boost::uint32_t m_button6 = 0;
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
            void setInputMethod(InputMethod *method, GameControl control);
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
