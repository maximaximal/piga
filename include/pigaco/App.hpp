#pragma once

#include <memory>

#include <piga/Host.hpp>
#include <piga/GameEventHandler.hpp>
#include <piga/GameInput.hpp>
#include <piga/PlayerManager.hpp>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QTimer>

namespace Wt
{
    class WServer;
}

namespace pigaco
{
    class DirectoryScanner;
    class Players;

    namespace packaging
    {
        class PackageManager;
    }

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

            std::shared_ptr<piga::Host> getHost();
            std::shared_ptr<piga::GameInput> getGameInput();
            std::shared_ptr<piga::PlayerManager> getPlayerManager();
            std::shared_ptr<packaging::PackageManager> getPackageManager();

            std::shared_ptr<DirectoryScanner> getDirectoryScanner();
            std::shared_ptr<Players> getPlayers();
        protected:
            void setEnd(bool state = true);
            virtual void onGameEvent(const piga::GameEvent &gameEvent, float frametime);

        public Q_SLOTS:
            void aboutToQuit();
            void update();

        private:
            std::shared_ptr<piga::Host> m_host;
            std::shared_ptr<piga::GameInput> m_gameInput;
            std::shared_ptr<piga::PlayerManager> m_playerManager;
            std::shared_ptr<packaging::PackageManager> m_packageManager;

            std::shared_ptr<DirectoryScanner> m_directoryScanner;
            std::shared_ptr<Players> m_players;

            QGuiApplication *m_guiApplication = nullptr;
            QQmlApplicationEngine *m_qmlApplicationEngine = nullptr;
            QQuickWindow *m_qQuickWindow = nullptr;
            QTimer *m_loopTimer = nullptr;

            Wt::WServer *m_webServer = nullptr;

            bool m_end = false;
            bool m_isSleeping = false;
    };
}
