#include <pihud/PushButton.hpp>

namespace PiH
{
    PushButton::PushButton(Widget *parent)
    	: Widget(parent)
    {
		m_backgroundImage = std::make_shared<Image>(this);
        m_buttonText = std::make_shared<Label>(this);
        m_buttonText->setCentered(true);
    }
    PushButton::~PushButton()
    {

    }
    void PushButton::onEvent(const Event &e)
    {
        Widget::onEvent(e);

        m_backgroundImage->onEvent(e);
        m_buttonText->onEvent(e);

        if(isFocused(e.playerID))
        {
			if(e.type == PiH::EventType::Piga)
			{
				if(e.piga.control == piga::ACTION && e.piga.state)
				{
					if(e.piga.state)
					{
						if(!m_pressed)
						{
							m_pressed = true;
							onButtonPressed(e.playerID);
							m_buttonPressedSignal(e.playerID);
						}
					}
					else
					{
						if(m_pressed)
						{
							m_pressed = false;
							onButtonReleased(e.playerID);
							m_buttonReleasedSignal(e.playerID);
						}
					}
				}
			}
        }
        else
        {
            if(m_pressed)
            {
                m_pressed = false;
                onButtonReleased(e.playerID);
                m_buttonReleasedSignal(e.playerID);
            }
        }
    }
    void PushButton::onUpdate(float frametime)
    {
		Widget::onUpdate(frametime);

        m_backgroundImage->onUpdate(frametime);
        m_buttonText->onUpdate(frametime);
    }
    void PushButton::onRender(SDL_Renderer *renderer, const FloatRect &offset)
    {
        m_backgroundImage->setTextureRect(getActiveTextureRect());
        m_backgroundImage->onRender(renderer, offset);
        m_buttonText->onRender(renderer, offset);
    }
    sigc::signal<void, int>& PushButton::getButtonPressedSignal()
    {
		return m_buttonPressedSignal;
    }
    sigc::signal<void, int>& PushButton::getButtonReleasedSignal()
    {
        return m_buttonReleasedSignal;
    }
    void PushButton::setFont(std::shared_ptr<Font> font)
    {
        m_buttonText->setFont(font);
    }
    void PushButton::setText(const std::string &text)
    {
        m_buttonText->setText(text);
    }
    void PushButton::setTextColor(SDL_Color color)
    {
        m_buttonText->setColor(color);
    }
    void PushButton::setTextColor(int r, int g, int b, int a)
    {
        m_buttonText->setColor(r, g, b, a);
    }
    const std::string& PushButton::getText()
    {
        return m_buttonText->getText();
    }
    void PushButton::setBackgroundTexture(std::shared_ptr<Texture> texture)
    {
        m_backgroundImage->setTexture(texture);
    }
    void PushButton::setNormalTextureRect(const IntRect &rect)
    {
		m_normalTextureRect = rect;
        setBoundingBox(getBoundingBox().x, getBoundingBox().y, rect.w, rect.h);
    }
    void PushButton::setFocusedTextureRect(const IntRect &rect)
    {
		m_focusedTextureRect = rect;
        setBoundingBox(getBoundingBox().x, getBoundingBox().y, rect.w, rect.h);
    }
    void PushButton::setPressedTextureRect(const IntRect &rect)
    {
		m_pressedTextureRect = rect;
        setBoundingBox(getBoundingBox().x, getBoundingBox().y, rect.w, rect.h);
    }
    void PushButton::updateBoundingBox()
    {
        m_backgroundImage->setBoundingBox(getBoundingBox());
        m_buttonText->setBoundingBox(getBoundingBox());
    }
    void PushButton::focusGained(int playerID)
    {
		//Nothing to do, handled by the event function.
    }
    void PushButton::focusLost(int playerID)
    {
		//Nothing to do, handled by the event function.
    }
    void PushButton::onButtonPressed(int playerID)
    {
		//Derivable by other classes.
    }
    void PushButton::onButtonReleased(int playerID)
    {
		//Derivable by other classes.
    }
    const IntRect &PushButton::getActiveTextureRect()
    {
        if(m_pressed)
        {
            return m_pressedTextureRect;
        }
        if(!m_pressed && isFocused())
        {
            return m_focusedTextureRect;
        }
        if(!m_pressed && !isFocused())
        {
            return m_normalTextureRect;
        }
    }
}
