#include <pihud/Font.hpp>
#include <iostream>
#include <SDL2/SDL_ttf.h>

using std::cout;
using std::endl;

namespace PiH
{
    Font::Font()
    {

    }
    Font::~Font()
    {
     	if(m_font != nullptr)
        {
            TTF_CloseFont(m_font);
        }
    }
    void Font::load(const std::string &fontPath)
    {
       	int ptSize = 16;
        if(fontPath.find(":") != std::string::npos)
        {
			//Get the font size from the last numbers after a ":" character in the name.
			ptSize = std::stoi(fontPath.substr(fontPath.find(":") + 1));
        }

        m_ptSize = ptSize;

        m_font = TTF_OpenFont(fontPath.substr(0, fontPath.find(":")).c_str(), ptSize);
        if(!m_font)
        {
            cout << "Error opening font! (TTF_OpenFont Error: " << TTF_GetError() << endl;
        }
    }
    TTF_Font *Font::getFont()
    {
        return m_font;
    }

    int Font::getPtSize()
    {
        return m_ptSize;
    }
}
