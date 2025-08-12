#pragma once
#include "Font.h"
#include "Widget.h"

namespace Biscuit::BCUI
{
    /// <summary>
    /// 进度条控件
    /// </summary>
    class ProgressBar : public Widget
    {
    public:
        ProgressBar();
        ProgressBar(const float& percentage);
        ProgressBar(Vec2 position, Vec2 size);
        ProgressBar(const float& percentage,Vec2 position);
        ProgressBar(const float& percentage,Vec2 position, Vec2 size);

        /// <summary>
        /// 设置进度条的文本内容
        /// </summary>
        /// <param name="text">文本</param>
        void SetText(const std::string& text);

        /// <summary>
        /// 获得进度条的文本内容
        /// </summary>
        /// <returns>文本内容</returns>
        std::string GetText() const;
        
        /// <summary>
        /// 获得当前进度
        /// </summary>
        /// <returns>进度（浮点数）</returns>
        float GetPercentage() const;

        /// <summary>
        /// 设置当前进度
        /// </summary>
        /// <param name="percentage">进度（浮点数）</param>
        void SetPercentage(float percentage);

        
        void SetLabelFont(std::shared_ptr<Font> font, int size);

        ImFont* GetLabelFont() const
        {
            return m_Font;
        }
        
        WidgetType GetWidgetType() const override;
    private:
        float           m_Progress;
        std::string     m_Text;
        ImFont*         m_Font = nullptr;
    };

}
