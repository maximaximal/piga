#pragma once

#include <string>

namespace pigaco
{
namespace packaging
{
/**
 * @brief The Version class provides logic for storing and handling version numbers.
 *
 * Version numbers are in the format \code 1.2.3:456
 */
class Version
{
    public:
        Version();
        Version(const std::string &stringRepresentation);
        Version(int major, int minor = 0, int mini = 0, int build = 0);
        virtual ~Version();

        std::string asString() const;

        static void parseVersion(const std::string &versionString, int &majorVersion, int &minorVersion, int &miniVersion, int &buildNumber);
        /**
         * @brief Compares two versions.
         * @return 1 if version two is greater than version one, -1 on the opposite, 0 if they are equal.
         */
        static int compareVersion(const std::string &one, const std::string &two);
        static int compareVersion(int oneMajor = 0, int twoMajor = 0, int oneMinor = 0, int twoMinor = 0,
                                  int oneMini = 0, int twoMini = 0, int oneBuild = 0, int twoBuild = 0);

        int getMajor() const;
        int getMinor() const;
        int getMini() const;
        int getBuild() const;

        void setMajor(int value);
        void setMinor(int value);
        void setMini(int value);
        void setBuild(int value);

        Version& operator=(Version &&other);
        Version& operator=(const Version &other);
    private:
        int m_major = 0;
        int m_minor = 0;
        int m_mini = 0;
        int m_build = 0;
};

bool operator< (const Version &one, const Version &two);
bool operator> (const Version &one, const Version &two);
}
}
