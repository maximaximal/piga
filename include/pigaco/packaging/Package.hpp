#pragma once

#include <string>
#include <map>
#include <pigaco/packaging/Version.hpp>

namespace pigaco
{
namespace packaging
{
class PackageManager;

class Package
{
    public:
        Package();
        virtual ~Package();

        void clearFlags();

        void fromPath(const std::string &path);
        void fromPPK(const std::string &filePath);
        void loadSpecs(const std::string &yamlString, bool autocorrect = false);
        void install();
        bool isValid();

        void saveToPPK(const std::string &destination);

        void fromDirectory(const std::string &dir);

        enum ConfigVar {
            Name,
            ID,
            PPKPath,
            Author,
            Version,
            Directory,

            _CONFIG_COUNT
        };
        enum Flag {
            IsInstalled,
            IsLoadedFromPPK,
            SpecsLoaded,
            IsInMainGamesList,

            HasPPK,
            HasAuthor,
            HasName,
            HasID,
            HasVersion,
            HasDirectory,

            _FLAG_COUNT
        };

        const std::string& getConfigVar(ConfigVar id);
        void setConfigVar(ConfigVar id, const std::string &var);
        std::string& operator[](ConfigVar id);

        void activateFlag(Flag flag);
        void disableFlag(Flag flag);
        bool flagActive(Flag flag);
        bool operator[](Flag flag);
        const packaging::Version& getVersion();

        void setPackageManager(PackageManager *pkgMgr);
        PackageManager* getPackageManager();

        static const char* getConfigVarName(ConfigVar var);
    private:
        void archiveInstall();
        void directoryInstall();
        
        std::map<ConfigVar, std::string> m_configVars;
        std::map<Flag, bool> m_flags;
        PackageManager *m_packageManager = nullptr;

        packaging::Version m_version;

        void autocorrectSpecs();
        bool m_isValid = true;
};
}
}
