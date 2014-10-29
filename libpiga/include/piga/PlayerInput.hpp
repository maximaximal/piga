#ifndef LIBPIGA_PIGA_PLAYERINPUT_HPP_INCLUDED
#define LIBPIGA_PIGA_PLAYERINPUT_HPP_INCLUDED

#include <map>
#include <vector>
#include <piga/GameControl.hpp>
#include <piga/InputMethod.hpp>

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
        protected:
            void update();

            int setInputMethod(InputMethod *method, GameControl control);
        private:
            std::map<GameControl, InputMethod*> m_inputMethods;
    };
}

#endif
