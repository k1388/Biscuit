#pragma once
#include "Widget.h"
namespace Biscuit::BCUI
{
    class Button : public Widget
    {
    public:
        Button();
        Button(const std::string& label);
        Button(Vec2 position, Vec2 size);
        Button(const std::string& label,Vec2 position);
        Button(const std::string& label,Vec2 position, Vec2 size);

        /// <summary>
        /// 设置按钮文字
        /// </summary>
        /// <param name="label">文字</param>
        inline void SetLabel(std::string& label) { m_Label = label; }
        std::string ToString() const override;
        
        /// <summary>
        /// 获取组件类型
        /// </summary>
        /// <returns>组件类型</returns>
        WidgetType GetWidgetType() const override;

        /// <summary>
        /// 获得按钮上的文字
        /// </summary>
        /// <returns>文字</returns>
        const std::string& GetLabel() const;
        
        using CallbackFn = std::function<void()>;

        /// <summary>
        /// 设置按钮的回调函数
        /// </summary>
        /// <param name="fn">回调函数</param>
        virtual void OnClick(CallbackFn fn);

        /// <summary>
        /// 触发回调
        /// </summary>
        void OnClickEvent();
    private:
        
        CallbackFn m_Callback = nullptr;
        std::string m_Label;
    };
}
