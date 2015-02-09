#pragma once

#include <memory>
#include <vector>
#include <pigaco/GameBox.hpp>
#include <SDL2/SDL.h>
#include <glm/vec2.hpp>
#include <pigaco/DirectoryScanner.hpp>
#include <pihud/TextureManager.hpp>
#include <pihud/Font.hpp>
#include <pihud/Widget.hpp>

namespace pigaco
{
    class GameChooser : public PiH::Widget
    {
        public:
            GameChooser(PiH::Widget *parent, std::shared_ptr<DirectoryScanner> directoryScanner);
            virtual ~GameChooser();
            
            void setDirectoryScanner(std::shared_ptr<DirectoryScanner> directoryScanner);
            std::shared_ptr<DirectoryScanner> getDirectoryScanner();
            
            virtual void onEvent(const PiH::Event &e);
            virtual void onUpdate(float frametime);
            virtual void onRender(SDL_Renderer *renderer, const PiH::FloatRect &offset);
            
            void setTextureManager(std::shared_ptr<PiH::TextureManager> textureManager);
            void setFont(std::shared_ptr<PiH::Font> font);
        private:
            std::shared_ptr<DirectoryScanner> m_directoryScanner;
            std::shared_ptr<PiH::TextureManager> m_textureManager;
            std::shared_ptr<PiH::Font> m_font;
            
            std::vector<std::shared_ptr<GameBox>> m_boxes;
    };
}
