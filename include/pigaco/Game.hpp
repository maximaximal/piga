#pragma once

#include <QObject>
#include <piga/GameHost.hpp>

namespace pigaco
{
class Game : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isRunning READ isRunning WRITE setRunning)

    public:
        enum ConfigValue
        {
            Name = piga::GameHost::Name,
            Description = piga::GameHost::Description,
            Version = piga::GameHost::Version,
            Author = piga::GameHost::Author,
            ProgramPath = piga::GameHost::ProgramPath,
            Parameters = piga::GameHost::Parameters,
            Directory = piga::GameHost::Directory,
            BackgroundImage = piga::GameHost::BackgroundImage,
            Logo = piga::GameHost::Logo,

            _COUN = piga::GameHost::_COUNT
        };

        Game();
        virtual ~Game();

        bool isRunning(bool fsCheck = false);
        bool isValid();

        void setRunning(bool state);

        Q_INVOKABLE void start();
        Q_INVOKABLE void exit();

        Q_ENUMS(ConfigValue)

        QString getConfig(ConfigValue id);
    private:
        piga::GameHost *m_gameHost = nullptr;
};
}
