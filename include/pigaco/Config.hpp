#pragma once

namespace pigaco
{
    class Config
    {
        public:
            Config();
            virtual ~Config();

            const std::string& getString();
    };
}
