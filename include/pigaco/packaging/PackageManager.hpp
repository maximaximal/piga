#pragma once

#include <unordered_map>
#include <list>
#include <string>
#include <memory>

namespace pigaco
{
namespace packaging
{
class Package;

typedef std::shared_ptr<Package> PackagePtr;
typedef std::list<PackagePtr> PackageList;
typedef std::unordered_map<std::string, PackagePtr> PackageMap;
        
class PackageManager
{
    public:
        PackageManager();
        virtual ~PackageManager();

        /**
         * @brief Returns a package by its unique ID. 
         * 
         * Does not take versions into consideration. 
         */
        PackagePtr getPackageFromID(const std::string &id);
        /**
         * @brief Returns the package by its name. 
         * 
         * Not guaranteed to be unique. 
         */
        PackageList getPackageFromName(const std::string &name);
        
        void installPackage(Package *package);
    private:
        PackageMap m_localPackages;
};
}
}
