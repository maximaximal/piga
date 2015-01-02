#ifndef LIBPIGA_PIGA_HOST_HPP_INCLUDED
#define LIBPIGA_PIGA_HOST_HPP_INCLUDED

#include <piga/GameInput.hpp>
#include <boost/interprocess/mapped_region.hpp>

namespace piga
{
    class GameHost;

    /**
     * @brief The Host class hosts the controls for all applications running on piga.
     *
     * This class has to be used by the master application which controls all other apps!
     */
    class Host
    {
        public:
            Host();
            virtual ~Host();

            void init();

            void applyFromGameInput(GameInput *gameInput);

            void setInput(unsigned int playerID, GameControl control, bool state);

            void setCurrentGameHost(std::shared_ptr<GameHost> gameHost);

            static std::string getSharedMemoryName();
            static std::string getGameInputInstanceName();
        protected:
            void createSharedMemory();
            void deleteSharedMemory();
        private:
            //Settings of the physical appearence of the console.
            unsigned int m_playerCount = 2;
            unsigned int m_buttonCount = 11;
            std::shared_ptr<GameHost> m_currentGameHost;
    };
}

#endif
