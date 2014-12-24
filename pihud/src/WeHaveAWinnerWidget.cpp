#include <pihud/WeHaveAWinnerWidget.hpp>

namespace PiH
{
    WeHaveAWinnerWidget::WeHaveAWinnerWidget(Widget *parent)
        : Widget(parent)
    {
        //Create internal widgets
            m_particleSource.reset(new ParticleSource(this));
            m_victoryImage.reset(new Image(this));
            m_playerNameDisplayLabel.reset(new Label(this));
            m_playerNameLabel.reset(new Label(this));

        //Assign values to the internal widgets.
            m_playerNameLabel->setText("We have a winner!");
            SDL_Color color;
            color.r = 255;
            color.g = 255;
            color.b = 255;
            m_playerNameLabel->setColor(color);
            m_playerNameDisplayLabel->setColor(color);
            m_particleSource->setTargetCount(80);
            m_particleSource->setDuration(10);
            m_particleSource->setGravity(-0.981);
            m_particleSource->setRotationSpeedRange(-50, 50);
            m_particleSource->setXSpeedRange(-180, 180);
            m_particleSource->setYSpeedRange(-250, -100);
            m_particleSource->setSpawnsPerFrame(0.18);
    }
    WeHaveAWinnerWidget::~WeHaveAWinnerWidget()
    {

    }
    void WeHaveAWinnerWidget::onUpdate(float frametime)
    {
        m_victoryImage->onUpdate(frametime);
        m_playerNameLabel->onUpdate(frametime);
        m_playerNameDisplayLabel->onUpdate(frametime);
        m_particleSource->onUpdate(frametime);


        m_time += frametime;
    }
    void WeHaveAWinnerWidget::onEvent(const Event &e)
    {
        m_victoryImage->onEvent(e);
        m_playerNameLabel->onEvent(e);
        m_playerNameDisplayLabel->onEvent(e);
        m_particleSource->onEvent(e);

        if(e.type == PiH::EventType::Input)
        {
            if(m_time > m_stayForSeconds)
            {
                m_done = true;
            }
        }
    }
    void WeHaveAWinnerWidget::onRender(SDL_Renderer *renderer, const FloatRect &offset)
    {
        SDL_Rect rect = getBoundingBox().toSDLRect();
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 150);
        SDL_RenderFillRect(renderer, &rect);

        m_particleSource->onRender(renderer, offset);
        m_victoryImage->onRender(renderer, offset);
        m_playerNameLabel->onRender(renderer, offset);
        m_playerNameDisplayLabel->onRender(renderer, offset);
    }
    void WeHaveAWinnerWidget::setWinnerName(std::string name)
    {
        m_playerNameDisplayLabel->setText(name);
    }
    bool WeHaveAWinnerWidget::isDone()
    {
        return m_done;
    }
    void WeHaveAWinnerWidget::setDone(bool done)
    {
        if(m_time > m_stayForSeconds)
            m_done = true;
    }
    void WeHaveAWinnerWidget::setStayForSeconds(float seconds)
    {
        m_stayForSeconds = seconds;
    }
    void WeHaveAWinnerWidget::setFont(std::shared_ptr<Font> font)
    {
        m_playerNameDisplayLabel->setFont(font);
        m_playerNameLabel->setFont(font);
    }
    void WeHaveAWinnerWidget::setVictoryImageTexture(std::shared_ptr<Texture> texture, const IntRect &rect)
    {
        m_victoryImage->setTexture(texture);
        m_victoryImage->setTextureRect(rect);
    }
    void WeHaveAWinnerWidget::setParticleTexture(std::shared_ptr<Texture> texture, const std::vector<IntRect> rects)
    {
        m_particleSource->setTexture(texture);
        m_particleSource->setTextureRectVector(rects);
    }
    void WeHaveAWinnerWidget::updateBoundingBox()
    {
        m_particleSource->setBoundingBox(m_boundingBox);
        m_victoryImage->setPosition(getBoundingBox().x + getBoundingBox().w / 2 - m_victoryImage->getBoundingBox().w / 2,
                                    10);

        m_playerNameLabel->setPosition(getBoundingBox().x + getBoundingBox().w / 2 - m_playerNameLabel->getBoundingBox().w / 2,
                                              getBoundingBox().y + getBoundingBox().h / 2 - getBoundingBox().y / 4 - m_playerNameLabel->getBoundingBox().h / 2);
        m_playerNameDisplayLabel->setPosition(getBoundingBox().x + getBoundingBox().w / 2 - m_playerNameDisplayLabel->getBoundingBox().w / 2,
                                       getBoundingBox().h / 4 * 3 - m_playerNameDisplayLabel->getBoundingBox().h / 2);

        m_particleSource->setXStartRange(getBoundingBox().w / 6 * 2, getBoundingBox().w / 6 * 4);
        m_particleSource->setYStartRange(getBoundingBox().y + getBoundingBox().h, getBoundingBox().y + getBoundingBox().h + 100);

        //Set the target count relative to the screen size. (Equals to 80 particles at 800x600)
        m_particleSource->setTargetCount(getBoundingBox().w * getBoundingBox().h / 6000);
    }
}
