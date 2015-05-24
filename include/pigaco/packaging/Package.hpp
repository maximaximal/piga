#pragma once

#include <string>
#include <map>

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

        void fromPPK(const std::string &filePath);
        void loadSpecs(const std::string &yamlString, bool autocorrect = false);
        void install();

        void fromDirectory(const std::string &dir);

        enum ConfigVar {
            Name,
            ID,
            PPKPath,
            Author,

            _CONFIG_COUNT
        };
        enum Flag {
            IsInstalled,
            IsLoadedFromPPK,
            SpecsLoaded,

            HasPPK,
            HasAuthor,
            HasName,
            HasID,

            _FLAG_COUNT
        };

        const std::string& getConfigVar(ConfigVar id);
        void setConfigVar(ConfigVar id, const std::string var);
        std::string& operator[](ConfigVar id);

        void activateFlag(Flag flag);
        void disableFlag(Flag flag);
        bool flagActive(Flag flag);
        bool operator[](Flag flag);

        void setPackageManager(PackageManager *pkgMgr);
        PackageManager* getPackageManager();

    private:
        std::map<ConfigVar, std::string> m_configVars;
        std::map<Flag, bool> m_flags;
        PackageManager *m_packageManager = nullptr;

        void autocorrectSpecs();
};
}
}
