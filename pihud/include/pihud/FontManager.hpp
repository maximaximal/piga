#pragma once

#include <pihud/Font.hpp>
#include <map>
#include <memory>
#include <string>

namespace PiH
{
    class FontManager
    {
        public:
            FontManager();
            virtual ~FontManager();

            virtual std::shared_ptr<Font> load(const std::string &fontPath);
            virtual std::shared_ptr<Font> get(const std::string &fontPath);

            bool has(const std::string &path);

            void destroy();
        private:
            std::map<std::string, std::weak_ptr<Font>> m_fonts;
    };
}
