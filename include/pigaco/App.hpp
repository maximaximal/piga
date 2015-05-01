#pragma once

#include <memory>

#include <piga/Host.hpp>
#include <piga/GameEventHandler.hpp>
#include <piga/GameInput.hpp>
#include <piga/PlayerManager.hpp>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>

namespace pigaco
{
    class Window;
    class DirectoryScanner;

    class App : public QObject, public piga::GameEventHandler
    {
        Q_OBJECT

        public:
            App();
            virtual ~App();

            void run(int argc, char *argv[]);

            void onUpdate(float frametime);

            bool end();

            void sleepWindow();
            void wakeupWindow();
        protected:
            void setEnd(bool state = true);
            virtual void onGameEvent(const piga::GameEvent &gameEvent, float frametime);

        public slots:
            void aboutToQuit();

        private:
            std::shared_ptr<piga::Host> m_host;
            std::shared_ptr<piga::GameInput> m_gameInput;
            std::shared_ptr<piga::PlayerManager> m_playerManager;
            
            std::shared_ptr<DirectoryScanner> m_directoryScanner;
            
            QGuiApplication *m_guiApplication = nullptr;
            QQmlApplicationEngine *m_qmlApplicationEngine = nullptr;
            QQuickWindow *m_qQuickWindow = nullptr;

            bool m_end = false;
            bool m_isSleeping = false;
    };
}
