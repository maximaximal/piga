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

            void run();

            void update(float frametime);

            bool end();
        protected:
            void setEnd(bool state = true);
        private:
            std::shared_ptr<piga::Host> m_host;

            std::unique_ptr<Window> m_window;

            bool m_end = false;
    };
}
