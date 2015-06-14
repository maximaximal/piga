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
#include <QTextStream>

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
void Package::fromPath(const std::string &path)
{
    setConfigVar(Directory, path);
    QFileInfo file(QString::fromStdString(path));
    if(file.isDir())
    {
        fromDirectory(path);
    }
    else
    {
        fromPPK(path);
    }
}
void Package::fromPPK(const std::string &filePath)
{
    LOG(INFO) << "Reading package from PPK \"" << filePath << "\".";
    activateFlag(IsLoadedFromPPK);
    setConfigVar(PPKPath, filePath);
    QuaZip ppk(QString::fromStdString(filePath));
    ppk.open(QuaZip::mdUnzip);

    ppk.setCurrentFile("PackageSpecs.yml");
    QuaZipFile specsFile(&ppk);
    specsFile.open(QIODevice::ReadOnly);
    QTextStream specsFileContents(&specsFile);
    loadSpecs(QString(specsFileContents.readAll()).toStdString());
}
void Package::loadSpecs(const std::string &yamlString, bool autocorrect)
{
    activateFlag(SpecsLoaded);

    YAML::Node specs = YAML::Load(yamlString);
    if(specs["PPKPath"])
    {
        setConfigVar(PPKPath, specs["PPKPath"].as<std::string>());
    }
    if(specs["Author"])
    {
        setConfigVar(Author, specs["Author"].as<std::string>());
    }
    if(specs["Name"])
    {
        setConfigVar(Name, specs["Name"].as<std::string>());
    }
    if(specs["Version"])
    {
        setConfigVar(Version, specs["Version"].as<std::string>());
    }
    if(specs["ID"])
    {
        setConfigVar(ID, specs["ID"].as<std::string>());
    }

    if(autocorrect)
    {
        autocorrectSpecs();
    }
}
void Package::install()
{
    if(m_packageManager != nullptr)
    {
        //Check if the package already exists. 
        PackagePtr package = m_packageManager->getPackageFromName(getConfigVar(Name));
        
        //Compare the versions if older version exist.
        if(package)
        {
            LOG(INFO) << "The package named \"" << getConfigVar(Name) << "\" is already installed. (Version: " << package->getVersion().asString() << ").";
            packaging::Version oldVersion = package->getVersion();
            if(oldVersion < getVersion())
            {
                LOG(INFO) << "Replacing older version " << package->getVersion().asString() << " of package \"" << getConfigVar(Name) << "\" with newer version " << getVersion().asString() << ".";
            }
            else
            {
                LOG(INFO) << "Replacing newer version " << package->getVersion().asString() << " of package \"" << getConfigVar(Name) << "\" with older version " << getVersion().asString() << ".";
            }
        }
    }
    
    if(flagActive(IsLoadedFromPPK))
    {
        //Install from archive
        archiveInstall();
    }
    else
    {
        //Install from directory
        directoryInstall();
    }
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
    out << YAML::BeginMap;

    for(auto &configVar : m_configVars)
    {
        out << YAML::Key << getConfigVarName(configVar.first);
        out << YAML::Value << configVar.second;
    }

    out << YAML::EndMap;

    std::ofstream outConfigFile(getConfigVar(Directory) + "/PackageSpecs.yml");
    outConfigFile << out.c_str();
    outConfigFile.close();

    LOG(INFO) << "Compressing PPK with destination \"" << destination << "\" and source \"" << getConfigVar(Directory) << "\".";

    JlCompress::compressDir(QString::fromStdString(destination),
                            QString::fromStdString(getConfigVar(Directory)),
                            true);
}
void Package::fromDirectory(const std::string &dir)
{
    LOG(INFO) << "Reading package from directory \"" << dir << "\".";
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
void Package::setConfigVar(Package::ConfigVar id, const std::string &var)
{
    m_configVars[id] = var;
    switch(id)
    {
        case pigaco::packaging::Package::Name:
            activateFlag(HasName);
            break;
        case pigaco::packaging::Package::ID:
            activateFlag(HasID);
            break;
        case pigaco::packaging::Package::PPKPath:
            activateFlag(HasPPK);
            break;
        case pigaco::packaging::Package::Author:
            activateFlag(HasAuthor);
            break;
        case pigaco::packaging::Package::Version:
            activateFlag(HasVersion);
            m_version = packaging::Version(var);
            break;
        case pigaco::packaging::Package::Directory:
            activateFlag(HasDirectory);
            break;
        default:
            break;
    }
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
    }
    if(!flagActive(HasID))
    {
        setConfigVar(ID, "---");
    }
    if(!flagActive(HasAuthor))
    {
        setConfigVar(Author, "No author given");
    }
}
void Package::archiveInstall()
{
    LOG(INFO) << "Extracting the package \"" << getConfigVar(PPKPath) << "\" named \"" << getConfigVar(Name) << "\" to \"" 
        << QDir::currentPath().toStdString() + "/Games/" + getConfigVar(Name) << "\".";
    JlCompress::extractDir(QString::fromStdString(getConfigVar(PPKPath)), QDir::currentPath() + "/Games/" + QString::fromStdString(getConfigVar(Name)));
    LOG(INFO) << "Successfully installed package named \"" << getConfigVar(Name) << "\" with version " << getVersion().asString() << ".";
}
void Package::directoryInstall()
{
    QString srcFilePath = QString::fromStdString(getConfigVar(Directory));
    QString tgtFilePath = QDir::currentPath() + "/Games/" + QString::fromStdString(getConfigVar(Name)); 
    
    LOG(INFO) << "Installing \"" << getConfigVar(Name) << "\" with version " << getVersion().asString() << " from \"" 
        << srcFilePath.toStdString() << "\" to \"" << tgtFilePath.toStdString() << "\".";
    
    QFileInfo srcFileInfo(srcFilePath);
    
    if (srcFileInfo.isDir()) {
        QDir targetDir(tgtFilePath);
        targetDir.cdUp();
        if (!targetDir.mkdir(QFileInfo(tgtFilePath).fileName()))
            LOG(FATAL) << "Install failure: Could not create target directory.";
        QDir sourceDir(srcFilePath);
        QStringList fileNames = sourceDir.entryList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden | QDir::System);
        Q_FOREACH(const QString &fileName, fileNames) {
            const QString newSrcFilePath
                    = srcFilePath + QLatin1Char('/') + fileName;
            const QString newTgtFilePath
                    = tgtFilePath + QLatin1Char('/') + fileName;
        }
    } else {
        if (!QFile::copy(srcFilePath, tgtFilePath))
            LOG(FATAL) << "Install failure.";
    }
}

}
}
