#pragma once

#include <string>
#include <map>
#include <SDL2/SDL.h>

#include <pihud/FocusManager.hpp>

namespace PiH
{
    class Config
    {
        public:
            Config(SDL_Renderer *renderer);
            virtual ~Config();

            void setupDefaultConfig();

            enum Variable
            {
                ZOOM,

                _COUNT
            };

            float getValueAsFloat(Config::Variable variable);
            int getValueAsInt(Config::Variable variable);
            const std::string &getValueAsString(Config::Variable variable);

            void setValueAsFloat(Config::Variable variable, float value);
            void setValueAsInt(Config::Variable variable, int value);
            void setValueAsString(Config::Variable variable, const std::string &value);

            SDL_Renderer *getSDLRenderer();
            std::shared_ptr<FocusManager> getFocusManager();
        private:
            std::map<Config::Variable, std::string> m_values;
            std::shared_ptr<FocusManager> m_focusManager;
            SDL_Renderer *m_sdlRenderer;
	};
}
