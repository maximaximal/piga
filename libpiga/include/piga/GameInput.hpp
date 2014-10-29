#ifndef LIBPIGA_PIGA_GAMEINPUT_HPP_INCLUDED
#define LIBPIGA_PIGA_GAMEINPUT_HPP_INCLUDED

#include <map>
#include <memory>

#include <piga/PlayerInput.hpp>

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

           	const PlayerInput& getPlayerInput(int id);
        private:
            std::map<int, std::shared_ptr<PlayerInput> > m_playerInputs;
            int m_playerInputIdCounter = 0;
    };
}

#endif
