#pragma once

#include <memory>

#include <piga/Host.hpp>

#include <pigaco/Window.hpp>

namespace pigaco
{
	class App
    {
        public:
            App();
            virtual ~App();


        private:
            std::shared_ptr<piga::Host> m_host;

            std::unique_ptr<Window> m_window;
    };
}
