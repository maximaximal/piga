#include <pigaco/packaging/Version.hpp>
#include <boost/lexical_cast.hpp>

namespace pigaco
{
namespace packaging
{

Version::Version()
{

}
Version::Version(const std::string &stringRepresentation)
{
    parseVersion(stringRepresentation, m_major, m_minor, m_mini, m_build);
}
Version::Version(int major, int minor, int mini, int build)
{
    m_major = major;
    m_minor = minor;
    m_mini = mini;
    m_build = build;
}
Version::~Version()
{

}
std::string Version::asString() const
{
    std::string out = "";

    out += boost::lexical_cast<std::string>(m_major) + ".";
    out += boost::lexical_cast<std::string>(m_minor) + ".";
    out += boost::lexical_cast<std::string>(m_mini) + ":";
    out += boost::lexical_cast<std::string>(m_build);

    return out;
}
void Version::parseVersion(const std::string &versionString, int &majorVersion, int &minorVersion, int &miniVersion, int &buildNumber)
{
    std::size_t pos = 0, start = 0;

    bool majorFound = false;
    bool minorFound = false;
    bool miniFound = false;
    bool buildFound = false;

    std::string numberCache;
    numberCache.resize(10);

    for(std::size_t i = 0; i < versionString.size(); ++i)
    {
        if(versionString[i] == '.' || versionString[i] == ':')
        {
            if(!majorFound)
            {
                majorVersion = boost::lexical_cast<int>(numberCache);
                majorFound = true;
            }
            else if(!minorFound)
            {
                minorVersion = boost::lexical_cast<int>(numberCache);
                minorFound = true;
            }
            else if(!miniFound)
            {
                miniVersion = boost::lexical_cast<int>(numberCache);
                miniFound = true;
            }

            numberCache.clear();

            if(versionString[i] == ':')
            {
                majorFound = true;
                minorFound = true;
                miniFound = true;
            }
            continue;
        }
        else
        {
            numberCache += versionString[i];
        }
    }

    if(numberCache.length() > 0)
    {
        if(!majorFound)
        {
            majorVersion = boost::lexical_cast<int>(numberCache);
        }
        else if(!minorFound)
        {
            minorVersion = boost::lexical_cast<int>(numberCache);
        }
        else if(!miniFound)
        {
            miniVersion = boost::lexical_cast<int>(numberCache);
        }
        else if(!buildFound)
        {
            buildNumber = boost::lexical_cast<int>(numberCache);
        }
    }
}
int Version::compareVersion(const std::string &one, const std::string &two)
{
    int oneMajor = 0, oneMinor = 0, oneMini = 0, oneBuild = 0;
    int twoMajor = 0, twoMinor = 0, twoMini = 0, twoBuild = 0;

    Version::parseVersion(one, oneMajor, oneMinor, oneMini, oneBuild);
    Version::parseVersion(two, twoMajor, twoMinor, twoMini, twoBuild);

    return compareVersion(oneMajor, twoMajor,
                          oneMinor, twoMinor,
                          oneMini, twoMini,
                          oneBuild, twoBuild);
}
int Version::compareVersion(int oneMajor, int twoMajor, int oneMinor, int twoMinor, int oneMini, int twoMini, int oneBuild, int twoBuild)
{
    if(oneMajor == twoMajor)
    {
        if(oneMinor == twoMinor)
        {
            if(oneMini == twoMini)
            {
                if(oneBuild == twoBuild)
                {
                    return 1;
                }
                else
                {
                    if(oneBuild > twoBuild)
                        return -1;
                    else
                        return 1;
                }
            }
            else
            {
                if(oneMini > twoMini)
                    return -1;
                else
                    return 1;
            }
        }
        else
        {
            if(oneMinor > twoMinor)
                return -1;
            else
                return 1;
        }
    }
    else
    {
        if(oneMajor > twoMajor)
            return -1;
        else
            return 1;
    }
}
int Version::getMajor() const
{
    return m_major;
}
int Version::getMinor() const
{
    return m_minor;
}
int Version::getMini() const
{
    return m_mini;
}
int Version::getBuild() const
{
    return m_build;
}
void Version::setMajor(int value)
{
    m_major = value;
}
void Version::setMinor(int value)
{
    m_minor = value;
}
void Version::setMini(int value)
{
    m_mini = value;
}
void Version::setBuild(int value)
{
    m_build = value;
}
Version &Version::operator=(Version &&other)
{
    m_major = other.getMajor();
    m_minor = other.getMinor();
    m_mini = other.getMini();
    m_build = other.getBuild();

    return *this;
}
Version &Version::operator=(const Version &other)
{
    if(this != &other)
    {
        m_major = other.getMajor();
        m_minor = other.getMinor();
        m_mini = other.getMini();
        m_build = other.getBuild();
    }
    return *this;
}
bool operator<(const Version &one, const Version &two)
{
    if(Version::compareVersion(one.getMajor(), two.getMajor(),
                      one.getMinor(), two.getMinor(),
                      one.getMini(), two.getMini(),
                      one.getBuild(), two.getBuild()) == -1)
    {
        return true;
    }
    return false;
}
bool operator>(const Version &one, const Version &two)
{
    if(Version::compareVersion(one.getMajor(), two.getMajor(),
                      one.getMinor(), two.getMinor(),
                      one.getMini(), two.getMini(),
                      one.getBuild(), two.getBuild()) == 1)
    {
        return true;
    }
    return false;
}

}
}
