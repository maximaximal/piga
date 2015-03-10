#include <pigaco/GameBox.hpp>
#include <easylogging++.h>

namespace pigaco
{
    GameBox::GameBox(PiH::Widget *parent)
        : Widget(parent)
    {
        m_image_background.reset(new PiH::Image());
        m_image_logo.reset(new PiH::Image());
        
        SDL_Color color;
        color.a = 255;
        color.r = 190;
        color.g = 190;
        color.b = 190;
        
        m_label_description.reset(new PiH::Label(this));
        m_label_name.reset(new PiH::Label(this));
        m_label_version.reset(new PiH::Label(this));
        
        m_label_description->setColor(color);
        m_label_name->setColor(color);
        m_label_version->setColor(color);
     
        m_backgroundRectColor.r = 214;
        m_backgroundRectColor.g = 214;
        m_backgroundRectColor.b = 214;
        m_backgroundRectColor.a = 20;
    }
    GameBox::~GameBox()
    {

    }
    void GameBox::onEvent(const PiH::Event &e)
    {
        m_image_background->onEvent(e);
        m_image_logo->onEvent(e);
        
        m_label_name->onEvent(e);
        m_label_description->onEvent(e);
        m_label_version->onEvent(e);
        
        if(e.type == PiH::EventType::Piga)
        {
            if(isFocused())
            {
                if(e.piga.control == piga::ACTION && m_gameHost)
                {
                    if(!m_gameHost->isRunning())
                    {
                        m_gameHost->start();
                    }
                }
            }
        }
    }
    void GameBox::onUpdate(float frametime)
    {
        m_image_background->onUpdate(frametime);
        m_image_logo->onUpdate(frametime);

        m_label_name->onUpdate(frametime);
        m_label_description->onUpdate(frametime);
        m_label_version->onUpdate(frametime);
    }
    void GameBox::onRender(SDL_Renderer *renderer, const PiH::FloatRect &floatRect)
    {
        Uint8 a, r, g, b;
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
        SDL_SetRenderDrawColor(renderer, m_backgroundRectColor.r,
            m_backgroundRectColor.g,
            m_backgroundRectColor.b,
            m_backgroundRectColor.a
        );
        SDL_Rect rect = getBoundingBox().toSDLRect();
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        
        
        m_image_background->onRender(renderer, floatRect);
        m_image_logo->onRender(renderer, floatRect);
        
        m_label_name->onRender(renderer, floatRect);
        m_label_description->onRender(renderer, floatRect);
        m_label_version->onRender(renderer, floatRect);
    }
    void GameBox::loadFromHost(std::shared_ptr<piga::GameHost> gameHost)
    {
        m_gameHost = gameHost;
        m_label_name->setText(gameHost->getConfig(piga::GameHost::Name));
        m_label_description->setText(gameHost->getConfig(piga::GameHost::Description));
        m_label_version->setText("V" + gameHost->getConfig(piga::GameHost::Version));
        
        if(m_textureManager)
        {
            m_image_background->setTexture(m_textureManager->getTexture(gameHost->getConfig(piga::GameHost::BackgroundImage)));
            m_image_background->setTextureRect(PiH::IntRect(0, 0, getBoundingBox().w, getBoundingBox().h));
            m_image_logo->setTexture(m_textureManager->getTexture(gameHost->getConfig(piga::GameHost::Logo)));
            m_image_logo->setTextureRect(PiH::IntRect(0, 0, 32, 32));
        }
    }
    void GameBox::setFont(std::shared_ptr<PiH::Font> font)
    {
        m_label_name->setFont(font);
        m_label_description->setFont(font);
        m_label_version->setFont(font);
    }
    void GameBox::setTextureManager(std::shared_ptr<PiH::TextureManager> textureManager)
    {
        m_textureManager = textureManager;
    }
    void GameBox::focusGained(int playerID)
    {
        if(playerID != -1)
        {
            m_backgroundRectColor.r = 255;
            m_backgroundRectColor.g = 189;
            m_backgroundRectColor.b = 97;
            m_backgroundRectColor.a = 80;
        }
    }
    void GameBox::focusLost(int playerID)
    {
        if(playerID != -1)
        {
            m_backgroundRectColor.r = 214;
            m_backgroundRectColor.g = 214;
            m_backgroundRectColor.b = 214;
            m_backgroundRectColor.a = 20;
        }
    }
    void GameBox::updateBoundingBox()
    {
        m_image_background->setPosition(getBoundingBox().x, getBoundingBox().y);
        m_image_background->setTextureRect(PiH::IntRect(0, 0, getBoundingBox().w, getBoundingBox().h));
        m_image_logo->setPosition(getBoundingBox().x + getBoundingBox().w - m_image_logo->getBoundingBox().w - 10, getBoundingBox().y - 10);
        
        m_label_name->setBoundingBox(PiH::FloatRect(getBoundingBox().x + 10, getBoundingBox().y + 10, getBoundingBox().w, getBoundingBox().h));
        m_label_description->setBoundingBox(PiH::FloatRect(getBoundingBox().x + 10, getBoundingBox().y + m_label_name->getTextHeight() + 25, getBoundingBox().w, getBoundingBox().h));
        m_label_version->setBoundingBox(PiH::FloatRect(getBoundingBox().x + 10, getBoundingBox().y + getBoundingBox().h - 10 - m_label_version->getTextHeight(), getBoundingBox().w, getBoundingBox().h));
    }
}
