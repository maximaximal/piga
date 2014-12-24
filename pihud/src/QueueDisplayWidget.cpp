#include <pihud/QueueDisplayWidget.hpp>

#include <iostream>

using std::cout;
using std::endl;

namespace PiH
{
    QueueDisplayWidget::QueueDisplayWidget(std::size_t queueSize, Widget *parent)
        : Widget(parent)
    {
        m_queueSize = queueSize;
        m_images.reserve(queueSize);
    }
    QueueDisplayWidget::~QueueDisplayWidget()
    {

    }
    void QueueDisplayWidget::clear()
    {
        m_images.clear();
    }
    void QueueDisplayWidget::onEvent(const Event &e)
    {

    }
    void QueueDisplayWidget::onUpdate(float frametime)
    {

    }
    void QueueDisplayWidget::onRender(SDL_Renderer *renderer, const FloatRect &offset)
    {
        for(auto &image : m_images)
        {
            if(m_backgroundImage)
            {
                m_backgroundImage->renderTo(image->getBoundingBox().x, image->getBoundingBox().y,
                                            renderer,
                                            offset);
            }
            image->onRender(renderer, offset);
        }
    }
    void QueueDisplayWidget::pushImage(std::unique_ptr<Image> image)
    {
        if(m_images.size() + 1 > m_queueSize)
        {
            m_images.erase(m_images.begin());
        }
        m_images.push_back(std::move(image));
        updateBoundingBox();
    }
    void QueueDisplayWidget::setBackgroundImage(std::unique_ptr<Image> image)
    {
        m_backgroundImage = std::move(image);
    }
    void QueueDisplayWidget::setQueueSize(std::size_t size)
    {
        m_queueSize = size;
        m_images.reserve(size);
    }
    std::size_t QueueDisplayWidget::getQueueSize()
    {
        return m_queueSize;
    }
    void QueueDisplayWidget::updateBoundingBox()
    {
        FloatRect box = getBoundingBox();

        box.w = 32;
        box.h = 32;

        for(std::size_t i = 0; i < m_images.size(); ++i)
        {
            m_images[i]->setBoundingBox(box);
            box.x += m_images[i]->getBoundingBox().w;
        }
    }
}
