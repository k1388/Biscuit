#include "pch.h"
#include "Button.h"

namespace Biscuit::BCUI
{
    std::string Button::ToString() const
    {
        std::stringstream ss;
        ss << "Button{" << """ << m_Name << "",pos:" << m_Position.ToString()<<"}"; 
        return ss.str();
    }

    Widget::WidgetType Button::GetWidgetType() const
    {
        return Widget::WidgetType::Button;
    }

    const std::string& Button::GetLabel() const
    {
        return m_Label;
    }

    void Button::OnClick(CallbackFn fn)
    {
        m_Callback = fn;
    }

    void Button::OnClickEvent()
    {
        if (m_Callback!=nullptr)
            m_Callback();
    }

    void Button::SetColor(Vec4 color)
    {
        m_Color = color;
    }

    Vec4 Button::GetColor()
    {
        return m_Color;
    }

    void Button::SetFrameRounding(float pixel)
    {
        m_FrameRounding = pixel;
    }

    float Button::GetFrameRounding()
    {
        return m_FrameRounding;
    }


    Button::Button():
    Widget("NewButton",Vec2(0,0), Vec2(100,40)),
    m_Label("NewButton")
    {
       ID++;
       m_Name = "NewButton" + std::to_string(ID);
    }

    Button::Button(const std::string& label):
    Widget("NewButton",Vec2(0,0), Vec2(100,40)),
    m_Label(label)
    {
        ID++;
        m_Name = "NewButton" + std::to_string(ID);
    }

    Button::Button(Vec2 position, Vec2 size):
    Widget("NewButton",position, size),
    m_Label("NewButton")
    {
        ID++;
        m_Name = "NewButton" + std::to_string(ID);
    }

    Button::Button(const std::string& label, Vec2 position):
    Widget("NewButton",position, Vec2(100,40)),
    m_Label(label)
    {
        ID++;
        m_Name = "NewButton" + std::to_string(ID);
    }

    Button::Button(const std::string& label, Vec2 position, Vec2 size):
    Widget("button",position, size),
    m_Label(label)
    {
        ID++;
        m_Name = "NewButton" + std::to_string(ID);
    }
}
