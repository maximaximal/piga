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
            Interface(bool selfhosted = false);
            virtual ~Interface();

            int getPlayerCount();
            const PlayerInput& getPlayerInput(int id);
            bool gameInputSet();

            bool pollEvent(GameEvent &event);
            bool isSelfhosted();
        private:
            GameInput *externalGameInput = nullptr;
            bool m_selfhosted;
    };
}

#endif
