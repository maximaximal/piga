#ifndef LIBPIGA_PIGA_INTERFACE_HPP_INCLUDED
#define LIBPIGA_PIGA_INTERFACE_HPP_INCLUDED

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
            Interface();
            virtual ~Interface();

            int getPlayerCount();
            const PlayerInput& getPlayerInput(int id);
            bool gameInputSet();

            bool pollEvent(GameEvent &event);
        private:
            GameInput *externalGameInput = nullptr;
    };
}

#endif
