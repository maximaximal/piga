#include <pigaco/GameChooser.hpp>

namespace pigaco 
{
    GameChooser::GameChooser(PiH::Widget *parent, std::shared_ptr<DirectoryScanner> directoryScanner)
        : m_directoryScanner(directoryScanner), PiH::Widget(parent)
    {
    
    }
    GameChooser::~GameChooser()
    {

    }
    void GameChooser::setDirectoryScanner(std::shared_ptr<DirectoryScanner> directoryScanner)
    {
        m_directoryScanner = directoryScanner;
    }
    std::shared_ptr<DirectoryScanner> GameChooser::getDirectoryScanner()
    {
        return m_directoryScanner;
    }
    void GameChooser::onEvent(const PiH::Event &e)
    {
        PiH::Widget::onEvent(e);
        for(auto &box : m_boxes)
        {
            box->onEvent(e);
        }
    }
    void GameChooser::onUpdate(float frametime)
    {
        PiH::Widget::onUpdate(frametime);
        for(auto &box : m_boxes)
        {
            box->onUpdate(frametime);
        }
    }
    void GameChooser::onRender(SDL_Renderer *renderer, const PiH::FloatRect &offset)
    {
        for(auto &box : m_boxes)
        {
            if(box->getBoundingBox().x + box->getBoundingBox().w > 0
                && box->getBoundingBox().x < getBoundingBox().w)
                box->onRender(renderer, offset);
        }
    }
    void GameChooser::setTextureManager(std::shared_ptr<PiH::TextureManager> textureManager)
    {
        m_textureManager = textureManager;
        for(auto &box : m_boxes)
        {
            box->setTextureManager(textureManager);
        }
    }
    void GameChooser::setFont(std::shared_ptr<PiH::Font> font)
    {
        m_font = font;
        for(auto &box : m_boxes)
        {
            box->setFont(font);
        }
    }
}