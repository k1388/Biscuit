#include "pch.h"
#include "Widget.h"

namespace Biscuit::BCUI
{
    int Widget::ID = 0;
    Widget::Widget(Vec2 position, Vec2 size) :
    m_Position(position), m_Size(size), m_Name(("NullWidget"))
    {}

    Widget::Widget(const std::string& name, Vec2 position, Vec2 size):
    m_Position(position), m_Size(size), m_Name(name)
    {}

    void Widget::SetPosition(Vec2 position)
    {
        m_Position = position;
    }

    void Widget::SetSize(Vec2 size)
    {
        m_Size = size;
    }

    std::string Widget::ToString() const
    {
        std::stringstream ss;
        ss << "Widget{" << """ << m_Name << "",pos:" << m_Position.ToString()<<"}"; 
        return ss.str();
    }

    void Widget::SetName(const std::string& name)
    {
        m_Name = name;
    }

    Widget::WidgetType Widget::GetWidgetType() const
    {
        return WidgetType::Null;
    }

    void Widget::SetVisible(bool visible)
    {
        m_IsVisible = visible;
    }

    bool Widget::GetVisible() const
    {
        return m_IsVisible;
    }
}
