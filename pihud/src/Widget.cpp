#include <pihud/Widget.hpp>

namespace PiH
{
    Widget::Widget(Widget *parent)
    {
		m_parent = parent;
    }
    Widget::~Widget()
    {

    }
    FloatRect &Widget::getBoundingBox()
    {
     	return m_boundingBox;
    }
    void Widget::setBoundingBox(float x, float y, float w, float h)
    {
        setBoundingBox(FloatRect(x, y, w, h));
    }
    void Widget::setBoundingBox(const FloatRect &box)
    {
        m_boundingBox = box;
        updateBoundingBox();
        updateParent();
    }
    void Widget::setPosition(float x, float y)
    {
        m_boundingBox.x = x;
        m_boundingBox.y = y;
        updateBoundingBox();
        updateParent();
    }
    void Widget::setWidth(float w)
    {
        m_boundingBox.w = w;
        updateBoundingBox();
        updateParent();
    }
    void Widget::setHeight(float h)
    {
        m_boundingBox.h = h;
        updateBoundingBox();
        updateParent();
    }
    bool Widget::isFocused()
    {
        return m_focused;
    }
    void Widget::onUpdate(float frametime)
    {

    }
    void Widget::onRender(SDL_Renderer *renderer, const FloatRect &offset)
    {

    }
    void Widget::updateRectFromBeneath()
    {

    }
    void Widget::updateParent()
    {
        if(m_parent != nullptr && !m_currentlyUpdating)
        {
            m_currentlyUpdating = true;
            m_parent->updateRectFromBeneath();
            m_currentlyUpdating = false;
        }
    }
}
