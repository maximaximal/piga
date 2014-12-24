#pragma once

#include <pihud/Config.hpp>

namespace PiH
{
    void initialize(Config *config);
    void exit();

    Config* getGlobalConfig();
}
