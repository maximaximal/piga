#pragma once

#include <QObject>
#include <piga/GameHost.hpp>

namespace pigaco
{
class Game : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isRunning READ isRunning WRITE setRunning)

    Q_PROPERTY(QString name READ getName)
    Q_PROPERTY(QString description READ getDescription)
    Q_PROPERTY(QString version READ getVersion)
    Q_PROPERTY(QString author READ getAuthor)

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
        Game(const Game &game);
        Game(piga::GameHost *gameHost);
        virtual ~Game();

        bool isRunning(bool fsCheck = false);
        bool isValid();

        void setRunning(bool state);
        piga::GameHost *getGameHost() const;

        Q_INVOKABLE void start();
        Q_INVOKABLE void exit();

        Q_ENUMS(ConfigValue)

        Q_INVOKABLE QString getConfig(ConfigValue id) const;
        const std::string& getConfig(piga::GameHost::ConfigValue id) const;

        QString getName() const;
        QString getDescription() const;
        QString getVersion() const;
        QString getAuthor() const;
    private:
        mutable piga::GameHost *m_gameHost = nullptr;
};
}

Q_DECLARE_METATYPE(pigaco::Game)
