#ifndef LIBPIGA_PIGA_SHAREDLIBLOADER_HPP
#define LIBPIGA_PIGA_SHAREDLIBLOADER_HPP

#include <string>
#include <memory>
#include <vector>
#include <map>

#include <piga/GameControl.hpp>

namespace piga
{
    class GameInput;
    class Host;

    class SharedLibWrapper
    {
        public:
            enum Type {
                Undefined,
                FixedFunction,
                InputMethods,

                _COUNT
            };

            SharedLibWrapper(const std::string &sharedObject);
            virtual ~SharedLibWrapper();

            void init(int playerCount);
            bool test();
            void destroy();

            int getMajorVersion();
            int getMinorVersion();
            int getMiniVersion();

            void query(Host* host, int playerID, GameControl input);
            int getButtonState(int playerID, GameControl button);
        private:
            std::vector<std::map<GameControl, int> > m_controls;
            std::string m_sharedObject;
            typedef int (*GetMajorVersion)();
            typedef int (*GetMinorVersion)();
            typedef int (*GetMiniVersion)();
            typedef int (*Init)();
            typedef void (*Destroy)();
            typedef int (*GetButtonState)(int, int);
            typedef void (*SetGameInput)(piga::GameInput);

            void *m_getMajorVersion = nullptr;
            void *m_getMinorVersion = nullptr;
            void *m_getMiniVersion = nullptr;
            void *m_init = nullptr;
            void *m_destroy = nullptr;
            void *m_getButtonState = nullptr;
            void *m_setGameInput = nullptr;

            void *m_dlHandle = nullptr;

            Type m_type = Undefined;
    };
}

#endif
