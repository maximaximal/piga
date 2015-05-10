#include <pigaco/GameHostStarter.hpp>
#include <QDir>

#include <easylogging++.h>

namespace pigaco
{

GameHostStarter::GameHostStarter()
    : QObject()
{
    m_gameProcess = new QProcess(this);

    connect(m_gameProcess, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(gameEnded(int,QProcess::ExitStatus)));
    connect(m_gameProcess, SIGNAL(started()), this, SLOT(gameStarted()));
    connect(m_gameProcess, SIGNAL(error(QProcess::ProcessError)), this, SLOT(gameError(QProcess::ProcessError)));
}

GameHostStarter::~GameHostStarter()
{
    if(isRunning(true))
        m_gameProcess->terminate();

    delete m_gameProcess;
}

bool GameHostStarter::isRunning(bool fsCheck)
{
    //FS-Check can be ignored, because the boolean is getting changed by an Qt event in this implementation
    //instead of a temporary file check.
    return m_running;
}

void GameHostStarter::startGame(const std::string &command, const std::string &arguments)
{
    LOG(INFO) << "Starting \"" << getConfig(ConfigValue::Name) << "\" with executable \"" << QDir::currentPath().toStdString() + "/" + command << "\".";
    LOG(INFO) << "Using arguments: \"" << arguments << "\"";
    m_gameProcess->start(QDir::currentPath() + "/" + QString::fromStdString(command) + " " + QString::fromStdString(arguments));
}

void GameHostStarter::gameEnded(int code, QProcess::ExitStatus status)
{
    m_running = false;
    QString exitStatus;

    switch(status)
    {
        case QProcess::NormalExit:
            exitStatus = "Normal";
            break;
        case QProcess::CrashExit:
            exitStatus = "Crashed";
            break;
    }

    LOG(INFO) << "Exited \"" << getConfig(ConfigValue::Name) << "\" with exit code \"" << exitStatus.toStdString() << "\".";
}

void GameHostStarter::gameStarted()
{
    m_running = true;
    LOG(INFO) << "Started \"" << getConfig(ConfigValue::Name) << "\"!";
}

void GameHostStarter::gameError(QProcess::ProcessError error)
{
    LOG(WARNING) << "There was an error while starting or running \"" << getConfig(ConfigValue::Name) << "\"!";
    switch(error)
    {
        case QProcess::ProcessError::FailedToStart:
            LOG(WARNING) << "The executable failed to start.";
            break;
        case QProcess::ProcessError::Crashed:
            LOG(WARNING) << "The game crashed!";
            break;
        case QProcess::ProcessError::Timedout:
            LOG(WARNING) << "The game timed out!";
            break;
        case QProcess::ProcessError::ReadError:
            LOG(WARNING) << "There was a read error!";
            break;
        case QProcess::ProcessError::WriteError:
            LOG(WARNING) << "There was a write error!";
            break;
        case QProcess::ProcessError::UnknownError:
            LOG(WARNING) << "The error was unknown!";
            break;
    }
}

}
