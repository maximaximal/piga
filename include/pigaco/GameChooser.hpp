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
#include <pihud/Layout.hpp>

namespace pigaco
{
    class GameChooser : public PiH::Layout
    {
        public:
            GameChooser(PiH::Widget *parent);
            virtual ~GameChooser();
            
            void setDirectoryScanner(std::shared_ptr<DirectoryScanner> directoryScanner);
            std::shared_ptr<DirectoryScanner> getDirectoryScanner();
            
            void setTextureManager(std::shared_ptr<PiH::TextureManager> textureManager);
            void setFont(std::shared_ptr<PiH::Font> font);
        private:
            std::shared_ptr<DirectoryScanner> m_directoryScanner;
            std::shared_ptr<PiH::TextureManager> m_textureManager;
            std::shared_ptr<PiH::Font> m_font;
    };
}
