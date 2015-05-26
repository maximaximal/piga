#include <pigaco/packaging/Package.hpp>
#include <pigaco/packaging/PackageManager.hpp>

#include <yaml-cpp/yaml.h>
#include <quazip/quazip.h>
#include <quazip/quazipfile.h>
#include <quazip/JlCompress.h>

#include <boost/lexical_cast.hpp>

#include <easylogging++.h>

#include <QFileDevice>
#include <QDir>

namespace pigaco
{
namespace packaging
{

Package::Package()
{
    clearFlags();
}
Package::~Package()
{

}
void Package::clearFlags()
{
    //Set all flags to false (not set)
    //This is the default value of all possible flags of a package.
    for(unsigned int i = 0; i < Flag::_FLAG_COUNT; ++i)
    {
        Flag flag = static_cast<Flag>(i);
        m_flags[flag] = false;
    }
}
void Package::fromPPK(const std::string &filePath)
{
    activateFlag(IsLoadedFromPPK);
    QuaZip ppk;

    QFile file(QString::fromStdString(filePath));
    ppk.setIoDevice(&file);

    ppk.setCurrentFile("PackageSpecs.yml");
    QuaZipFile specsFile;
    specsFile.setZip(&ppk);
    loadSpecs(specsFile.readAll().toStdString());
}
void Package::loadSpecs(const std::string &yamlString, bool autocorrect)
{
    activateFlag(SpecsLoaded);

    YAML::Node specs = YAML::Load(yamlString);
    if(specs["PPKPath"])
    {
        setConfigVar(PPKPath, specs["PPKPath"].as<std::string>());
        activateFlag(HasPPK);
    }
    if(specs["Author"])
    {
        setConfigVar(Author, specs["Author"].as<std::string>());
        activateFlag(HasAuthor);
    }
    if(specs["Name"])
    {
        setConfigVar(Name, specs["Name"].as<std::string>());
        activateFlag(HasName);
    }
    if(specs["Version"])
    {
        setConfigVar(Version, specs["Version"].as<std::string>());
        activateFlag(HasVersion);

        m_version = packaging::Version(getConfigVar(Version));
    }
    if(specs["ID"])
    {
        setConfigVar(ID, specs["ID"].as<std::string>());
        activateFlag(HasID);
    }

    if(autocorrect)
    {
        autocorrectSpecs();
    }
}
void Package::install()
{

}
void Package::saveToPPK(const std::string &destination)
{
    if(!flagActive(HasName))
    {
        LOG(FATAL) << "Package cannot be created, the package has no name!";
        return;
    }
    if(!flagActive(HasDirectory))
    {
        LOG(FATAL) << "Package \"" << getConfigVar(Name) << "\" has no directory! No PPK/ZIP file can be created without a source.";
        return;
    }
    if(!flagActive(HasAuthor))
    {
        LOG(WARNING) << "The package \"" << getConfigVar(Name) << "\" has no author specified. The author field will be left blank.";
    }
    if(!flagActive(HasVersion))
    {
        LOG(WARNING) << "The package \"" << getConfigVar(Name) << "\" has no version specified! You will not be able to update this package automaticly.";
    }


    YAML::Emitter out;
    out << YAML::BeginSeq;

    for(auto &configVar : m_configVars)
    {
        out << YAML::Key << getConfigVarName(configVar.first);
        out << YAML::Value << configVar.second;
    }

    out << YAML::EndSeq;

    std::ofstream outConfigFile(getConfigVar(Directory) + "/PackageSpecs.yml");
    outConfigFile << out.c_str();
    outConfigFile.close();

    JlCompress::compressDir(QString::fromStdString(destination),
                            QString::fromStdString(getConfigVar(Directory)),
                            true);
}
void Package::fromDirectory(const std::string &dir)
{
    setConfigVar(Directory, dir);
    activateFlag(HasDirectory);

    QFile specsFile(QString::fromStdString(dir + "/PackageSpecs.yml"));
    if(specsFile.isReadable())
    {
        loadSpecs(specsFile.readAll().toStdString());
    }
    else
    {
        LOG(WARNING) << "The package in the directory \"" << dir << "\" has no \"PackageSpecs.yml\" file!";
    }
}
const std::string &Package::getConfigVar(Package::ConfigVar id)
{
    return m_configVars[id];
}
void Package::setConfigVar(Package::ConfigVar id, const std::string var)
{
    m_configVars[id] = var;
}
std::string &Package::operator[](Package::ConfigVar id)
{
    return m_configVars[id];
}
void Package::activateFlag(Package::Flag flag)
{
    m_flags[flag] = true;
}
void Package::disableFlag(Package::Flag flag)
{
    m_flags[flag] = false;
}
bool Package::flagActive(Package::Flag flag)
{
    return m_flags[flag];
}
bool Package::operator[](Package::Flag flag)
{
    return flagActive(flag);
}
const Version &Package::getVersion()
{
    return m_version;
}
void Package::setPackageManager(PackageManager *pkgMgr)
{
    m_packageManager = pkgMgr;
}
PackageManager *Package::getPackageManager()
{
    return m_packageManager;
}
const char *Package::getConfigVarName(Package::ConfigVar var)
{
    switch(var)
    {
        case pigaco::packaging::Package::Name:
            return "Name";
            break;
        case pigaco::packaging::Package::ID:
            return "ID";
            break;
        case pigaco::packaging::Package::PPKPath:
            return "PPKPath";
            break;
        case pigaco::packaging::Package::Author:
            return "Author";
            break;
        case pigaco::packaging::Package::Version:
            return "Version";
            break;
        case pigaco::packaging::Package::Directory:
            return "Directory";
            break;
        default:
            return "";
            break;
    }
}
void Package::autocorrectSpecs()
{
    if(!flagActive(HasName))
    {
        setConfigVar(Name, "Undefined Name");
        activateFlag(HasName);
    }
    if(!flagActive(HasID))
    {
        setConfigVar(ID, "---");
        activateFlag(HasID);
    }
    if(!flagActive(HasAuthor))
    {
        setConfigVar(Author, "No author given");
        activateFlag(HasAuthor);
    }
}

}
}
