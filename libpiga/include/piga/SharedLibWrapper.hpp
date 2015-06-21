#ifndef LIBPIGA_PIGA_SHAREDLIBLOADER_HPP
#define LIBPIGA_PIGA_SHAREDLIBLOADER_HPP

#include <string>
#include <memory>
#include <vector>
#include <map>
#include <functional>

#include <piga/GameControl.hpp>

namespace piga
{
    class GameInput;
    class Host;

    class SharedLibWrapper
    {
        public:
            typedef std::function<void(int, int, int)> InputCallbackFunction;
            enum Type {
                Undefined,
                FixedFunction,
                InputMethods,
                InputCallback,

                _COUNT
            };

            SharedLibWrapper(const std::string &sharedObject);
            virtual ~SharedLibWrapper();

            void init(int playerCount);
            bool test();
            void destroy();

            int getPigaMajorVersion();
            int getPigaMinorVersion();
            int getPigaMiniVersion();

            const char* getName();
            const char* getDescription();
            const char* getAuthor();

            void query(Host* host, int playerID, GameControl input);
            int getButtonState(int playerID, GameControl button);
            void setInputCallback(InputCallbackFunction &callback);

            void inputCallback(int controlCode, int playerID, int value);
        private:
            std::vector<std::map<GameControl, int> > m_controls;
            std::string m_sharedObject;
            typedef int (*GetPigaMajorVersion)();
            typedef int (*GetPigaMinorVersion)();
            typedef int (*GetPigaMiniVersion)();
            typedef int (*Init)();
            typedef void (*Destroy)();
            typedef int (*GetButtonState)(int, int);
            typedef void (*SetGameInput)(piga::GameInput);
            typedef const char*(*GetString)(void);
            typedef void (*InputCallbackFunctionType)(int, int, int);
            typedef void (*SetInputCallback)(InputCallbackFunctionType*);

            void *m_getPigaMajorVersion = nullptr;
            void *m_getPigaMinorVersion = nullptr;
            void *m_getPigaMiniVersion = nullptr;
            void *m_init = nullptr;
            void *m_destroy = nullptr;
            void *m_getButtonState = nullptr;
            void *m_setGameInput = nullptr;
            void *m_setInputCallback = nullptr;

            void *m_getName = nullptr;
            void *m_getDescription = nullptr;
            void *m_getAuthor = nullptr;

            void *m_dlHandle = nullptr;

            InputCallbackFunction m_inputCallbackFunction;

            Type m_type = Undefined;
    };
}

#endif
