#pragma once

#include <unordered_map>
#include <list>
#include <string>
#include <memory>

namespace pigaco
{
class DirectoryScanner;

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

        void saveData(const std::string &datafile);
        void readData(const std::string &datafile, const std::string &dir);
        PackageMap& getPackages();

        /**
         * @brief Returns the package by its name. 
         */
        PackagePtr getPackageFromName(const std::string &name);
        bool packageExists(const std::string &name);
        
        void installPackage(Package *package);

        /**
         * @brief Loads a temporary package into the package manager. 
         *
         * Temporary packages are not saved and are cleared from the package
         * manager after it was shut down. They exist to provide a check 
         * against already installed packages with the same name or other discrepancies.
         *
         * @param path The path to the package (directory or PPK)
         *
         * @return A PackagePtr to the loaded package.
         */
        PackagePtr getTempPackage(const std::string &path);
        bool tempPackageExists(const std::string &path);
        void deleteTempPackage(const std::string &path);
    private:
        PackageMap m_localPackages;
        std::unordered_map<std::string, std::weak_ptr<Package> > m_tempPackages;
};
}
}
