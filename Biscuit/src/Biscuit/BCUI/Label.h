#pragma once
#include "Widget.h"
#include "Biscuit/Math/Vec2.h"

namespace Biscuit::BCUI
{
    class BISCUIT_API Label : public Widget
    {
    public:
        Label();
        Label(const std::string& label);
        Label(Vec2 position, Vec2 size);
        Label(const std::string& label,Vec2 position);
        Label(const std::string& label,Vec2 position, Vec2 size);

        /// <summary>
        /// 获得Label中的文本
        /// </summary>
        /// <returns>Label文本</returns>
        std::string GetText();
        
        /// <summary>
        /// 设置Label中的文本
        /// </summary>
        /// <param name="text">文本</param>
        inline void SetText(const std::string& text);
        inline WidgetType GetWidgetType() const override;
        inline std::string ToString() const override;

        
    private:
        std::string m_Text;
    };
}
