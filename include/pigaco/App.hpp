#pragma once

#include <memory>

#include <SDL2/SDL_events.h>

#include <piga/Host.hpp>
#include <piga/GameEventHandler.hpp>
#include <piga/GameInput.hpp>
#include <piga/PlayerManager.hpp>

#include <pihud/HudContainer.hpp>

namespace pigaco
{
    class Window;
    class DirectoryScanner;

    class App : public piga::GameEventHandler
    {
        public:
            App();
            virtual ~App();

            void run();

            void onEvent(const SDL_Event &e, float frametime);
            void onUpdate(float frametime);

            bool end();

            void sleepWindow();
            void wakeupWindow();
        protected:
            void setEnd(bool state = true);
            virtual void onGameEvent(const piga::GameEvent &gameEvent, float frametime);

        private:
            std::shared_ptr<piga::Host> m_host;
            std::shared_ptr<piga::GameInput> m_gameInput;
            std::shared_ptr<piga::PlayerManager> m_playerManager;

            std::unique_ptr<Window> m_window;
            std::unique_ptr<DirectoryScanner> m_directoryScanner;

            PiH::HudContainer *m_hudContainer = nullptr;

            bool m_end = false;
            bool m_isSleeping = false;
    };
}
