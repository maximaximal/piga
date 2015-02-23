#include <pigaco/GameChooser.hpp>
#include <easylogging++.h>

#include <pihud/pihud.hpp>

namespace pigaco 
{
    GameChooser::GameChooser(PiH::Widget *parent)
        : PiH::Layout(parent)
    {
        
    }
    GameChooser::~GameChooser()
    {

    }
    void GameChooser::setDirectoryScanner(std::shared_ptr<DirectoryScanner> directoryScanner)
    {
        m_directoryScanner = directoryScanner;
        for(auto &game : directoryScanner->getGames())
        {
            std::shared_ptr<GameBox> box = std::make_shared<GameBox>(this);
            box->setFont(m_font);
            box->setTextureManager(m_textureManager);
            box->loadFromHost(game.second);
            box->setBoundingBox(PiH::FloatRect(0, 0, 300, getBoundingBox().h));
            if(isFocused() && m_widgets.size() == 0)
            {
                PiH::getGlobalConfig()->getFocusManager()->setFocused(box, 0);
            }
            m_widgets.push_back(std::static_pointer_cast<PiH::Widget>(box));
        }
    }
    std::shared_ptr<DirectoryScanner> GameChooser::getDirectoryScanner()
    {
        return m_directoryScanner;
    }
    void GameChooser::setTextureManager(std::shared_ptr<PiH::TextureManager> textureManager)
    {
        m_textureManager = textureManager;
        for(auto &box : m_widgets)
        {
            std::static_pointer_cast<GameBox>(box)->setTextureManager(textureManager);
        }
    }
    void GameChooser::setFont(std::shared_ptr<PiH::Font> font)
    {
        m_font = font;
        for(auto &box : m_widgets)
        {
            std::static_pointer_cast<GameBox>(box)->setFont(font);
        }
    }
    void GameChooser::updateBoundingBox()
    {
        PiH::Layout::updateBoundingBox();
    }
}
