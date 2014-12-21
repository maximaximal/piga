#ifndef LIBPIGA_PIGA_HOST_HPP_INCLUDED
#define LIBPIGA_PIGA_HOST_HPP_INCLUDED

#include <piga/GameInput.hpp>

namespace piga
{
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

            void update();

            GameInput *getGameInput();

            static std::string getSharedMemoryName();
            static std::string getGameInputInstanceName();
        protected:
            void createSharedMemory();
            void deleteSharedMemory();
        private:
            GameInput *m_gameInput = nullptr;
    };
}

#endif
