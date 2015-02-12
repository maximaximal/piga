#include <pihud/HealthAndNameDisplay.hpp>

namespace PiH
{
    HealthAndNameDisplay::HealthAndNameDisplay(Widget *parent)
    	: Widget(parent)
    {
        m_label = new Label(this);
        m_iconHealthIndicator = new IconHealthIndicator(this);

        SDL_Color labelColor;
        labelColor.r = 81;
        labelColor.g = 81;
        labelColor.b = 204;
        m_label->setColor(labelColor);
    }
    HealthAndNameDisplay::~HealthAndNameDisplay()
    {
		delete m_label;
        delete m_iconHealthIndicator;
    }
    void HealthAndNameDisplay::setTexture(std::shared_ptr<Texture> texture)
    {
		m_iconHealthIndicator->setTexture(texture);
        updateBoundingBox();
    }
    void HealthAndNameDisplay::setFont(std::shared_ptr<Font> font)
    {
		m_label->setFont(font);
    }
    void HealthAndNameDisplay::setName(std::string text)
    {
        m_label->setText(text);
    }
    void HealthAndNameDisplay::setDistance(int distance)
    {
        m_distance = distance;
        updateBoundingBox();
    }
    void HealthAndNameDisplay::setCurrentHealth(int health)
    {
        m_iconHealthIndicator->setCurrentHealth(health);
    }
    void HealthAndNameDisplay::setSideOfIcons(Direction side)
    {
        m_sideOfIcons = side;
    }
    IconHealthIndicator *HealthAndNameDisplay::getHealthIndicator()
    {
		return m_iconHealthIndicator;
    }
    Label *HealthAndNameDisplay::getLabel()
    {
        return m_label;
    }
    void HealthAndNameDisplay::onEvent(const Event &e)
    {
        
    }
    void HealthAndNameDisplay::onRender(SDL_Renderer *renderer, const FloatRect &offset)
    {
        m_label->onRender(renderer, offset);
        m_iconHealthIndicator->onRender(renderer, offset);
    }
    void HealthAndNameDisplay::updateRectFromBeneath()
    {
        FloatRect boundingBox = getBoundingBox();

        boundingBox.w = m_label->getBoundingBox().w;
        boundingBox.h = m_label->getBoundingBox().h + m_distance
                + m_iconHealthIndicator->getBoundingBox().h;


        if(boundingBox != getBoundingBox())
        {
            setBoundingBox(boundingBox);
        }
    }
    void HealthAndNameDisplay::updateBoundingBox()
    {
        m_boundingBox.w = m_label->getBoundingBox().w;
        m_boundingBox.h = m_label->getBoundingBox().h + m_distance
                + m_iconHealthIndicator->getBoundingBox().h;

        m_label->setBoundingBox(FloatRect(m_boundingBox.x,
                             			  m_boundingBox.y,
                                          m_boundingBox.w,
                                          18));

        m_iconHealthIndicator->setBoundingBox(FloatRect(m_boundingBox.x,
                                           				m_boundingBox.y + m_label->getBoundingBox().h + m_distance,
                                                        m_boundingBox.w,
                                                        32));
    }
}
