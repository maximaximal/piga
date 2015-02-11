#include <pihud/ParticleSource.hpp>

namespace PiH
{
    ParticleSource::ParticleSource(Widget *parent)
        : Widget(parent)
    {

    }
    ParticleSource::~ParticleSource()
    {

    }
    void ParticleSource::setTargetCount(long count)
    {
        m_targetCount = count;
    }
    void ParticleSource::setTexture(std::shared_ptr<Texture> texture)
    {
        m_texture = texture;
        for(auto &particle : m_particles)
        {
            particle->texture = texture;
        }
    }
    void ParticleSource::setTextureRectVector(const std::vector<IntRect> &textureRects)
    {
        m_textureRects = textureRects;
        m_distribution = std::uniform_int_distribution<int>(0,textureRects.size() - 1);
    }
    void ParticleSource::setDuration(float time)
    {
        m_duration = time;
    }
    void ParticleSource::setGravity(float gravity)
    {
        m_gravity = gravity;
    }
    void ParticleSource::setSpawnsPerFrame(float count)
    {
        m_spawnsPerFrame = count;
    }
    void ParticleSource::setXSpeedRange(float min, float max)
    {
        m_xSpeedRange = std::uniform_real_distribution<float>(min, max);
    }
    void ParticleSource::setYSpeedRange(float min, float max)
    {
        m_ySpeedRange = std::uniform_real_distribution<float>(min, max);
    }
    void ParticleSource::setRotationSpeedRange(float min, float max)
    {
        m_rotationSpeedRange = std::uniform_real_distribution<float>(min, max);
    }
    void ParticleSource::setXStartRange(float min, float max)
    {
        m_xStartRange = std::uniform_real_distribution<float>(min, max);
    }
    void ParticleSource::setYStartRange(float min, float max)
    {
        m_yStartRange = std::uniform_real_distribution<float>(min, max);
    }
    bool ParticleSource::isFinished()
    {
        if(m_time > m_duration)
            return true;
        return false;
    }
    void ParticleSource::onUpdate(float frametime)
    {
        m_currentFrameSpawns += m_spawnsPerFrame;
        m_time += frametime;
        for(auto it = m_particles.begin(); it != m_particles.end(); ++it)
        {
            (*it)->onUpdate(frametime, m_gravity);
            if(((*it)->getX() + (*it)->getTextureRect().w < 0
                    || (*it)->getX() > getBoundingBox().x + getBoundingBox().w
                    || (*it)->getY() > getBoundingBox().y + getBoundingBox().h + (*it)->getTextureRect().h)
                    && (*it)->velY > 1)
            {
                m_particles.erase(it);
            }
        }
        while(spawnMoreParticles())
        {
            m_currentFrameSpawns -= 1;
            addParticle();
        }
    }
    void ParticleSource::onEvent(const Event &e)
    {

    }
    void ParticleSource::onRender(SDL_Renderer *renderer, const FloatRect &offset)
    {
        for(auto &particle : m_particles)
        {
            particle->onRender(renderer);
        }
    }
    void ParticleSource::addParticle()
    {
        int textureRect = m_distribution(m_generator);
        std::unique_ptr<Particle> particle(new Particle());
        particle->setTextureRect(m_textureRects[textureRect]);
        particle->texture = m_texture;
        particle->setX(m_xStartRange(m_generator));
        particle->setY(m_yStartRange(m_generator));

        particle->velX = m_xSpeedRange(m_generator);
        particle->velY = m_ySpeedRange(m_generator);

        particle->rotationSpeed = m_rotationSpeedRange(m_generator);

        m_particles.push_back(std::move(particle));
    }
    bool ParticleSource::spawnMoreParticles()
    {
        if(m_particles.size() < m_targetCount && m_currentFrameSpawns > 0)
            return true;
        return false;
    }
    void ParticleSource::updateBoundingBox()
    {

    }

}
