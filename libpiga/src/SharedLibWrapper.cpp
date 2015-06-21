#include <piga/SharedLibWrapper.hpp>
#include <piga/GameInput.hpp>
#include <piga/Definitions.hpp>
#include <dlfcn.h>
#include <iostream>

#include <host.h>

#include <piga/Host.hpp>

using std::cout;
using std::endl;

namespace piga
{
    SharedLibWrapper::SharedLibWrapper(const std::string &sharedObject)
        : m_sharedObject(sharedObject)
    {
        //Try to open the handle.
        m_dlHandle = dlopen(sharedObject.c_str(), RTLD_LAZY);

        if(m_dlHandle != nullptr)
        {
            //Load informational functions.
            m_getMajorVersion = dlsym(m_dlHandle, "getMajorVersion");
            m_getMinorVersion = dlsym(m_dlHandle, "getMinorVersion");
            m_getMiniVersion = dlsym(m_dlHandle, "getMiniVersion");
            m_getName = dlsym(m_dlHandle, "getName");
            m_getDescription = dlsym(m_dlHandle, "getDescription");
            m_getAuthor = dlsym(m_dlHandle, "getAuthor");
        }
        else
        {
            cout << PIGA_DEBUG_PRESTRING << "The shared object \"" << sharedObject << "\" could not be loaded!" << endl;
        }
    }
    SharedLibWrapper::~SharedLibWrapper()
    {
        destroy();
    }
    void SharedLibWrapper::init(int playerCount)
    {
        destroy();

        m_dlHandle = dlopen(m_sharedObject.c_str(), RTLD_LAZY);

        //Load functions
        m_getButtonState = dlsym(m_dlHandle, "getButtonState");
        m_setGameInput = dlsym(m_dlHandle, "setGameInput");
        m_init = dlsym(m_dlHandle, "init");
        m_destroy = dlsym(m_dlHandle, "destroy");
        m_getMajorVersion = dlsym(m_dlHandle, "getMajorVersion");
        m_getMinorVersion = dlsym(m_dlHandle, "getMinorVersion");
        m_getMiniVersion = dlsym(m_dlHandle, "getMiniVersion");
        m_getName = dlsym(m_dlHandle, "getName");
        m_getDescription = dlsym(m_dlHandle, "getDescription");
        m_getAuthor = dlsym(m_dlHandle, "getAuthor");

        if(test())
        {
            //Init the library
            int code = ((Init) m_init)();
            switch(code)
            {
                case HOST_RETURNCODE_USEFIXEDFUNCTION:
                    m_type = FixedFunction;
                    m_controls.resize(playerCount);
                    for(auto &controls : m_controls)
                    {
                        for(auto &control : controls)

                        {
                            control.second = 0;
                        }
                    }
                    cout << PIGA_DEBUG_PRESTRING << "Loading host library with the fixed function pipeline." << endl;
                    break;
                case HOST_RETURNCODE_USEINPUTMETHODS:
                    cout << PIGA_DEBUG_PRESTRING << "Loading host library with the input method pipeline." << endl;
                    m_type = InputMethods;
                    m_controls.clear();
                    break;
                case HOST_RETURNCODE_USECALLBACK:
                    cout << PIGA_DEBUG_PRESTRING << "Loading host library with the callback pipeline." << endl;
                    m_type = InputCallback;
                    m_setInputCallback = dlsym(m_dlHandle, "setInputCallback");
                    setInputCallback(m_inputCallbackFunction);
                    break;
                default:
                    m_type = Undefined;
                    break;
            }
            cout << PIGA_DEBUG_PRESTRING << "Loaded shared object \"" << getName() << "\" with the API-Version " << getMajorVersion() << "." << getMinorVersion() << "." << getMiniVersion()
                 << " - piga is running on " << HOST_VERSION_MAJOR << "." << HOST_VERSION_MINOR << "." << HOST_VERSION_MINI << "." << endl;
        }
        else
        {
            cout << PIGA_DEBUG_PRESTRING << "Shared object \"" << m_sharedObject << "\" could not be loaded because of an API version mismatch!" << endl;
            cout << PIGA_DEBUG_PRESTRING << "The shared object was compiled with Piga Host API-Version " << getMajorVersion() << "." << getMinorVersion() << "." << getMiniVersion()
                 << ", while piga is running on " << HOST_VERSION_MAJOR << "." << HOST_VERSION_MINOR << "." << HOST_VERSION_MINI << "." << endl;
        }
    }
    bool SharedLibWrapper::test()
    {
        if(HOST_VERSION_MAJOR != getMajorVersion())
        {
            return false;
        }
        if(HOST_VERSION_MINOR != getMinorVersion())
        {
            return false;
        }
        if(HOST_VERSION_MINI != getMiniVersion())
        {
            return true;
        }
        return true;
    }
    void SharedLibWrapper::destroy()
    {
        if(m_dlHandle != nullptr)
        {
            cout << PIGA_DEBUG_PRESTRING << "Destroyed shared library \"" << getName() << "\"." << endl;

            dlclose(m_dlHandle);
            m_dlHandle = nullptr;

            m_getMajorVersion = nullptr;
            m_getMinorVersion = nullptr;
            m_getMiniVersion = nullptr;
            m_init = nullptr;
            m_destroy = nullptr;
            m_getButtonState = nullptr;
            m_setGameInput = nullptr;
            m_getName = nullptr;
            m_getDescription = nullptr;
            m_getAuthor = nullptr;
            m_setInputCallback = nullptr;
        }
    }
    int SharedLibWrapper::getMajorVersion()
    {
        return ((GetMajorVersion) m_getMajorVersion)();
    }
    int SharedLibWrapper::getMinorVersion()
    {
        return ((GetMinorVersion) m_getMinorVersion)();
    }
    int SharedLibWrapper::getMiniVersion()
    {
        return ((GetMiniVersion) m_getMiniVersion)();
    }
    const char* SharedLibWrapper::getName()
    {
        if(m_getName != nullptr)
            return ((GetString) m_getName)();
        else
            return "";
    }
    const char* SharedLibWrapper::getDescription()
    {
        if(m_getDescription != nullptr)
            return ((GetString) m_getDescription)();
        else
            return "";
    }
    const char* SharedLibWrapper::getAuthor()
    {
        if(m_getAuthor != nullptr)
            return ((GetString) m_getAuthor)();
        else
            return "";
    }
    void SharedLibWrapper::query(Host *host, int playerID, GameControl input)
    {
        if(m_type == FixedFunction)
        {
            int result = getButtonState(playerID, input);

            if(m_controls[playerID][input] != result)
            {
                if(result == 0)
                    host->setInput(playerID, input, false);
                else
                    host->setInput(playerID, input, true);
                
                m_controls[playerID][input] = result;
            }

            m_controls[playerID][input] = result;
        }
    }
    int SharedLibWrapper::getButtonState(int playerID, GameControl button)
    {
        return ((GetButtonState) m_getButtonState)(playerID, GameControlToHostDefine(button));
    }
    void SharedLibWrapper::setInputCallback(InputCallbackFunction &callback)
    {
        // Convert the internal function pointer to the input callback handler function to a C-style function pointer.
        ((SetInputCallback) m_setInputCallback)(m_inputCallbackFunction.target<InputCallbackFunctionType>());
    }
    void SharedLibWrapper::inputCallback(int controlCode, int playerID, int value)
    {
        m_controls[playerID][HostDefineToGameControl(controlCode)] = value;
    }
}
