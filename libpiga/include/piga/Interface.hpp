#ifndef LIBPIGA_PIGA_INTERFACE_HPP_INCLUDED
#define LIBPIGA_PIGA_INTERFACE_HPP_INCLUDED

#include <bitset>
#include <piga/PlayerInput.hpp>
#include <piga/GameInput.hpp>
#include <piga/GameEvent.hpp>

namespace piga
{
    /**
     * @brief The Interface class provides a simplified interface to the shared controls.
     *
     * This object has to be deleted before the global GameInput object is deleted!
     */
    class Interface
    {
        public:
            Interface(bool selfhosted = false);
            virtual ~Interface();

            int getPlayerCount();
            const PlayerInput& getPlayerInput(int id);
            bool gameInputSet();
            int addPlayerInput(std::shared_ptr<PlayerInput> playerInput);

            bool pollEvent(GameEvent &event);
            bool isSelfhosted();
            void update();
        private:
			std::deque<GameEvent> events;
            GameInput *externalGameInput = nullptr;
            bool m_selfhosted;
            std::vector<PlayerInputStruct> m_playerInputs;
    };
}

#endif
