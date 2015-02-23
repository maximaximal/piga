#include <pihud/IconHealthIndicator.hpp>

namespace PiH
{
    IconHealthIndicator::IconHealthIndicator(Widget *parent)
        : Widget(parent)
    {

    }
    IconHealthIndicator::~IconHealthIndicator()
    {

    }
    int IconHealthIndicator::getCurrentHealth()
    {
        return m_currentHealth;
    }
    int IconHealthIndicator::getMaximumHealth()
    {
        return m_maximumHealth;
    }
    void IconHealthIndicator::setCurrentHealth(int health)
    {
        if(health != m_currentHealth)
        {
            if(health > m_maximumHealth)
                health = m_maximumHealth;
            if(health < 0)
                health = 0;
            m_currentHealth = health;
            updateCurrent();
        }
    }
    void IconHealthIndicator::setMaximumHealth(int maximumHealth)
    {
        if(maximumHealth != m_maximumHealth)
        {
            m_maximumHealth = maximumHealth;
            updateMaximum();
        }
    }
    void IconHealthIndicator::setFullIcon(const IntRect &rect)
    {
        m_fullIcon = rect;
        for(auto & icon : m_icons)
        {
            icon->setTextureRect(rect);
        }
        updateDimensions();
    }
    void IconHealthIndicator::setDepletedIcon(const IntRect &rect)
    {
        m_depletedIcon = rect;
        for(auto & icon : m_icons)
        {
            icon->setTextureRect(rect);
        }
        updateDimensions();
    }
    void IconHealthIndicator::setSideOfIcons(Direction side)
    {
        m_sideOfIcons = side;
    }
    void IconHealthIndicator::setTexture(std::shared_ptr<Texture> texture)
    {
        m_texture = texture;
        updateTexture();
    }
    void IconHealthIndicator::onEvent(const Event &e)
    {

    }
    void IconHealthIndicator::onRender(SDL_Renderer *renderer, const FloatRect &offset)
    {
        for(auto & icon : m_icons)
        {
            icon->onRender(renderer, offset);
        }
    }
    void IconHealthIndicator::updateMaximum()
    {
        if(m_icons.size() > m_maximumHealth)
        {
            m_icons.erase(m_icons.begin() + m_maximumHealth - 1,
                          m_icons.begin() + m_icons.size() - 1);
        }
        else
            if(m_icons.size() < m_maximumHealth)
            {
                while(m_icons.size() < m_maximumHealth)
                {
                    std::unique_ptr<Image> icon(new Image(this));
                    icon->setTexture(m_texture);
                    icon->setTextureRect(m_fullIcon);
                    m_icons.push_back(std::move(icon));
                }
            }
        updateBoundingBox();
    }
    void IconHealthIndicator::updateCurrent()
    {
        for(std::size_t i = 0; i < m_currentHealth; ++i)
        {
            m_icons[i]->setTextureRect(m_fullIcon);
        }
        for(std::size_t i = m_currentHealth; i < m_icons.size(); ++i)
        {
            m_icons[i]->setTextureRect(m_depletedIcon);
        }
    }
    void IconHealthIndicator::updateTexture()
    {
        for(auto & icon : m_icons)
        {
            icon->setTexture(m_texture);
        }
    }
    void IconHealthIndicator::updateBoundingBox()
    {
        updateDimensions();

        float x = m_boundingBox.x, y = m_boundingBox.y;
        FloatRect box;
        box.y = y;
        box.w = 32;
        box.h = 32;

        for(std::size_t i = 0; i < m_icons.size(); ++i)
        {
            if(m_sideOfIcons == LEFT)
            {
                box.x = x + m_fullIcon.w * i;
            }
            else
            {
                box.x = x + m_boundingBox.w - (m_fullIcon.w * i);
            }
            m_icons[i]->setBoundingBox(box);
        }
    }

    void IconHealthIndicator::updateDimensions()
    {
        FloatRect boundingBox = m_boundingBox;
        bool changed = false;

        if(m_fullIcon.h != boundingBox.h)
        {
            boundingBox.h = m_fullIcon.h;
            changed = true;
        }
        if(m_icons.size() * m_fullIcon.w != m_boundingBox.w)
        {
            boundingBox.w = m_icons.size() * m_fullIcon.w;
            changed = true;
        }
        if(changed)
        {
            this->setBoundingBox(boundingBox);
        }
    }
}
