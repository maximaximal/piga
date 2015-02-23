#pragma once

#include <memory>
#include <pihud/Widget.hpp>
#include <pihud/Label.hpp>
#include <pihud/Image.hpp>
#include <pihud/Font.hpp>
#include <pihud/TextureManager.hpp>
#include <piga/GameHost.hpp>

namespace pigaco
{
    /**
     * @brief Describes the image with text for a game host in a game chooser list.
     * 
     */
    class GameBox : public PiH::Widget
    {
        public:
            GameBox(PiH::Widget *parent = nullptr);
            virtual ~GameBox();

            virtual void onEvent(const PiH::Event &e);
            virtual void onUpdate(float frametime);
            virtual void onRender(SDL_Renderer *renderer, const PiH::FloatRect &floatRect);

            void loadFromHost(std::shared_ptr<piga::GameHost> gameHost);
            
            void setFont(std::shared_ptr<PiH::Font> font);
            void setTextureManager(std::shared_ptr<PiH::TextureManager> textureManager);
        protected:
            virtual void focusGained(int playerID);
            virtual void focusLost(int playerID);
        private:
            virtual void updateBoundingBox();
            std::shared_ptr<piga::GameHost> m_gameHost;
            std::shared_ptr<PiH::TextureManager> m_textureManager;
            
            std::unique_ptr<PiH::Image> m_image_background;
            std::unique_ptr<PiH::Image> m_image_logo;
            
            std::unique_ptr<PiH::Label> m_label_name;
            std::unique_ptr<PiH::Label> m_label_description;
            std::unique_ptr<PiH::Label> m_label_version;
    };
}
