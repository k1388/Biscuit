#pragma once
#include "Widget.h"

namespace Biscuit::BCUI
{
    class ProgressBar : public Widget
    {
    public:
        ProgressBar();
        ProgressBar(const float& percentage);
        ProgressBar(Vec2 position, Vec2 size);
        ProgressBar(const float& percentage,Vec2 position);
        ProgressBar(const float& percentage,Vec2 position, Vec2 size);

        void SetText(const std::string& text);
        std::string GetText() const;
        
        float GetPercentage() const;
        WidgetType GetWidgetType() const override;
    private:
        float m_Progress;
        std::string m_Text;
    };

}
