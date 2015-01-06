#include <pihud/FontManager.hpp>
#include <iostream>

using std::cout;
using std::endl;

namespace PiH
{
    FontManager::FontManager()
    {
        cout << "TEST" << endl;
    }
    FontManager::~FontManager()
    {
        destroy();
    }
    std::shared_ptr<Font> FontManager::load(const std::string &fontPath)
    {
        std::shared_ptr<Font> font = std::make_shared<Font>();
        font->load(fontPath);

        m_fonts[fontPath] = font;

        return font;
    }
    std::shared_ptr<Font> FontManager::get(const std::string &fontPath)
    {
        std::shared_ptr<Font> font;
        if(!has(fontPath))
        {
            font = load(fontPath);
        }
        else
        {
            font = m_fonts[fontPath].lock();
        }
        return font;
    }
    bool FontManager::has(const std::string &path)
    {
        if(m_fonts.count(path) > 0)
        {
            if(!m_fonts[path].expired())
            {
                return true;
            }
            else
            {
                m_fonts.erase(path);
            }
        }
        return false;
    }
    void FontManager::destroy()
    {
        for(auto font : m_fonts)
        {
            if(!font.second.expired())
            {
                auto sharedFont = font.second.lock();
                sharedFont->destroy();
                sharedFont.reset();
            }
        }
        m_fonts.clear();
    }
}
