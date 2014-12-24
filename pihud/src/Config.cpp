#include <pihud/Config.hpp>

namespace PiH
{
    Config::Config(SDL_Renderer *renderer)
    {
		m_sdlRenderer = renderer;
    }
    Config::~Config()
    {

    }
    void Config::setupDefaultConfig()
    {
        //Set the default zoom to 1.
		setValueAsFloat(Config::Variable::ZOOM, 1);
    }
    float Config::getValueAsFloat(Config::Variable variable)
    {
        float value;
        value = std::atof(m_values[variable].c_str());
        return value;
    }
    int Config::getValueAsInt(Config::Variable variable)
    {
		int value;
        value = std::atoi(m_values[variable].c_str());
        return value;
    }
    const std::string& Config::getValueAsString(Config::Variable variable)
    {
		return m_values[variable];
    }
    void Config::setValueAsFloat(Config::Variable variable, float value)
    {
		m_values[variable] = std::to_string(value);
    }
    void Config::setValueAsInt(Config::Variable variable, int value)
    {
		m_values[variable] = std::to_string(value);
    }
    void Config::setValueAsString(Config::Variable variable, const std::string &value)
    {
        m_values[variable] = value;
    }
    SDL_Renderer *Config::getSDLRenderer()
    {
        return m_sdlRenderer;
    }
}
