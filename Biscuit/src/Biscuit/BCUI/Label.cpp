#include "pch.h"
#include "Label.h"

namespace Biscuit::BCUI
{
   Label::Label():
   Widget("NewButton",Vec2(0,0), Vec2(50,20)),
   m_Text("NewButton")
    {
        ID++;
        m_Name = "NewButton" + std::to_string(ID);
    }

    Label::Label(const std::string& label):
    Widget("NewButton",Vec2(0,0), Vec2(50,20)),
    m_Text(label)
    {
        ID++;
        m_Name = "NewButton" + std::to_string(ID);
    }

    Label::Label(Vec2 position, Vec2 size):
    Widget("NewButton",position, size),
    m_Text("NewButton")
    {
        ID++;
        m_Name = "NewButton" + std::to_string(ID);
    }

    Label::Label(const std::string& label, Vec2 position):
    Widget("NewButton",position, Vec2(50,20)),
    m_Text(label)
    {
        ID++;
        m_Name = "NewButton" + std::to_string(ID);
    }

    Label::Label(const std::string& label, Vec2 position, Vec2 size):
    Widget("button",position, size),
    m_Text(label)
    {
        ID++;
        m_Name = "NewButton" + std::to_string(ID);
    }

    std::string Label::GetText()
    {
       return m_Text;
    }

    void Label::SetText(const std::string& text)
    {
       m_Text = text;
    }

    Widget::WidgetType Label::GetWidgetType() const
    {
        return Widget::WidgetType::Label;
    }

    std::string Label::ToString() const
    {
       std::stringstream ss;
       ss << "Label{" << """ << m_Name << "",pos:" << m_Position.ToString()<<"}"; 
       return ss.str();
    }

    void Label::SetLabelFont(std::shared_ptr<Font> font, int size)
    {
       m_Font = font->GetFontBySize(size);
    }
}
