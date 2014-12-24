#pragma once

#include <memory>

#include <SDL2/SDL_events.h>

#include <piga/Host.hpp>
#include <piga/GameEventHandler.hpp>
#include <piga/GameInput.hpp>

#include <pihud/HudContainer.hpp>

#include <pigaco/Window.hpp>

namespace pigaco
{
    class App : public piga::GameEventHandler
    {
        public:
            App();
            virtual ~App();

            void run();

            void onEvent(const SDL_Event &e, float frametime);
            void onUpdate(float frametime);

            bool end();
        protected:
            void setEnd(bool state = true);
            virtual void onGameEvent(const piga::GameEvent &gameEvent, float frametime);

        private:
            std::shared_ptr<piga::Host> m_host;
            std::shared_ptr<piga::GameInput> m_gameInput;

            std::unique_ptr<Window> m_window;

            PiH::HudContainer *m_hudContainer = nullptr;

            bool m_end = false;
    };
}
