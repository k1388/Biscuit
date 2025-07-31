#include "pch.h"
#include "ProgressBar.h"

namespace Biscuit::BCUI
{
    ProgressBar::ProgressBar():
    Widget("NewProgressBar",Vec2(0, 0),Vec2(75,15)),
    m_Progress(0.5f)
    {
        ID++;
        m_Name = "NewProgressBar" + std::to_string(ID);
    }

    ProgressBar::ProgressBar(const float& percentage):
    Widget("NewProgressBar",Vec2(0, 0),Vec2(75,15)),
    m_Progress(percentage)
    {
    }

    ProgressBar::ProgressBar(Vec2 position, Vec2 size):
    Widget("NewProgressBar",position,size),
    m_Progress(0.5f)
    {
    }

    ProgressBar::ProgressBar(const float& percentage, Vec2 position):
    Widget("NewProgressBar",position,Vec2(75,15)),
    m_Progress(percentage)
    {
    }

    ProgressBar::ProgressBar(const float& percentage, Vec2 position, Vec2 size):
    Widget("NewProgressBar",position,size),
    m_Progress(percentage)
    {
    }

    void ProgressBar::SetText(const std::string& text)
    {
        m_Text = text;
    }

    std::string ProgressBar::GetText() const
    {
        return m_Text;
    }

    float ProgressBar::GetPercentage() const
    {
        return m_Progress;
    }

    void ProgressBar::SetPercentage(float percentage)
    {
        m_Progress = percentage;
    }

    void ProgressBar::SetLabelFont(std::shared_ptr<Font> font, int size)
    {
        m_Font = font->GetFontBySize(size);
    }

    Widget::WidgetType ProgressBar::GetWidgetType() const
    {
        return Widget::WidgetType::ProgressBar;
    }
}
