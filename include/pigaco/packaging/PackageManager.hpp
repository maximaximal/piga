#pragma once

#include <unordered_map>
#include <string>
#include <memory>

namespace pigaco
{
namespace packaging
{
class Package;

class PackageManager
{
    public:
        PackageManager();
        virtual ~PackageManager();

        std::shared_ptr<Package> getPackage(const std::string &id);
    private:
        std::unordered_map<std::string, std::shared_ptr<Package>> m_localPackages;
};
}
}
