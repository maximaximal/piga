#include <pihud/pihud.hpp>

namespace PiH
{
    Config *GlobalConfig = nullptr;
    void initialize(Config *config)
    {
        if(GlobalConfig == nullptr)
        {
            GlobalConfig = config;
        }
    }
    void exit()
    {
        if(GlobalConfig != nullptr)
        {
            delete GlobalConfig;
        }
    }
    Config *getGlobalConfig()
    {
        if(GlobalConfig == nullptr)
        {
            GlobalConfig = new Config(nullptr);
            GlobalConfig->setupDefaultConfig();
        }
        return GlobalConfig;
    }
}
