#pragma once

#include <QProcess>
#include <piga/GameHost.hpp>

namespace pigaco
{
class GameHostStarter : public QObject, public piga::GameHost
{
        Q_OBJECT
    public:
        GameHostStarter();
        virtual ~GameHostStarter();

        virtual bool isRunning(bool fsCheck);
    protected:
        virtual void startGame(const std::string &command, const std::string &arguments);
    public slots:
        void gameEnded(int code, QProcess::ExitStatus status);
        void gameStarted();
        void gameError(QProcess::ProcessError error);
    private:
        QProcess *m_gameProcess = nullptr;
};
}
