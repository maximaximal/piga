#include <pigaco/packaging/PackageManager.hpp>
#include <pigaco/packaging/Package.hpp>
#include <yaml-cpp/yaml.h>
#include <pigaco/DirectoryScanner.hpp>
#include <easylogging++.h>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace pigaco
{
namespace packaging
{

PackageManager::PackageManager()
{

}
PackageManager::~PackageManager()
{

}
void PackageManager::saveData(const std::string &datafile)
{
    //Nothing to do yet; There is no metadata saved with installations. 
}
void PackageManager::readData(const std::string &datafile, const std::string &dir)
{
    //Read the Games/ subdirectory
    LOG(INFO) << "Scanning directory \"" << dir << "\".";
    if(!fs::exists(dir))
    {
        LOG(FATAL) << "The path \"" << dir.c_str() << "\" does not exist!";
        return;
    }
    if(!fs::is_directory(dir))
    {
        LOG(FATAL) << "The path \"" << dir.c_str() << "\" is not a directory!";
        return;
    }
    fs::directory_iterator end_it;
    for(fs::directory_iterator it(dir); it != end_it; ++it)
    {
        if(fs::is_directory(it->status()))
        {
            //Load the package and add it to the internal map.
            PackagePtr package = std::make_shared<Package>();
            package->fromDirectory(it->path().string());
            m_localPackages[package->getConfigVar(Package::Name)] = package;
        }
    }
    LOG(INFO) << "Scan completed!";
}
PackageMap& PackageManager::getPackages()
{
    return m_localPackages;
}
PackagePtr PackageManager::getPackageFromName(const std::string &name)
{
    if(m_localPackages.count(name) > 0)
        return m_localPackages[name];
    else 
        return PackagePtr(nullptr);
}
bool PackageManager::packageExists(const std::string &name)
{
    if(m_localPackages.count(name) > 0)
    {
        return true;
    }
    return false;
}
void PackageManager::installPackage(Package *package)
{
    PackagePtr pack(package);
    
    pack->install();
    m_localPackages[pack->getConfigVar(Package::Name)] = std::move(pack);
}
PackagePtr PackageManager::getTempPackage(const std::string &path)
{
    if(tempPackageExists(path))
    {
        return m_tempPackages[path].lock();
    }
    PackagePtr pack(new Package());
    pack->fromPath(path);
    m_tempPackages[path] = pack;
    return pack;
}
void PackageManager::deleteTempPackage(const std::string &path)
{
    if(tempPackageExists(path))
    {
        m_tempPackages.erase(path);
    }
}
bool PackageManager::tempPackageExists(const std::string &path)
{
    if(m_tempPackages.count(path) > 0)
    {
        return true;
    }
    return false;
}
}
}
