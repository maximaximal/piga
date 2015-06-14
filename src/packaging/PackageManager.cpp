#include <pigaco/packaging/PackageManager.hpp>
#include <pigaco/packaging/Package.hpp>

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
PackagePtr PackageManager::getPackageFromName(const std::string &name)
{
    if(m_localPackages.count(name) > 0)
        return m_localPackages[name];
    else 
        return PackagePtr(nullptr);
}
void PackageManager::installPackage(Package *package)
{
    PackagePtr pack(package);
    
    pack->install();
    m_localPackages[pack->getConfigVar(Package::Name)] = std::move(pack);
}

}
}
