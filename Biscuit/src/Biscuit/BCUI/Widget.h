#pragma once
#include "../Math/Vec2.h"
namespace Biscuit::BCUI
{
    class Widget
    {
    public:
        enum class WidgetType
        {
            Null,
            Button,
            Label,
            ProgressBar
        };
        static int ID;

        Widget(Vec2 position, Vec2 size);
        Widget(const std::string& name, Vec2 position, Vec2 size);

        /// <summary>
        /// 设置组件位置
        /// </summary>
        /// <param name="position">位置坐标</param>
        inline void SetPosition(Vec2 position);

        /// <summary>
        /// 设置组件大小
        /// </summary>
        /// <param name="size">大小</param>
        inline void SetSize(Vec2 size);

        virtual inline std::string ToString() const;

        /// <summary>
        /// 设置组件名称
        /// </summary>
        /// <param name="name">名称</param>
        virtual void SetName(const std::string& name);

        /// <summary>
        /// 获取组件类型
        /// </summary>
        /// <returns>组件类型</returns>
        virtual inline WidgetType GetWidgetType() const;

        /// <summary>
        /// 获取组件位置
        /// </summary>
        /// <returns>组件位置坐标</returns>
        inline Vec2 GetPosition() const
        {return m_Position;}

        /// <summary>
        /// 获取组件大小
        /// </summary>
        /// <returns>组件大小</returns>
        inline Vec2 GetSize() const
        {return m_Size;}

        /// <summary>
        /// 获取组件名称
        /// </summary>
        /// <returns>组件名称</returns>
        inline std::string GetName() const
        {return m_Name;}

        /// <summary>
        /// 设置组件可视性
        /// </summary>
        /// <param name="visible">可视性</param>
        void SetVisible(bool visible);

        /// <summary>
        /// 获取组件可视性
        /// </summary>
        /// <returns>可视性</returns>
        bool GetVisible() const;
    protected:
        Vec2 m_Position;
        Vec2 m_Size;
        std::string m_Name;
        bool m_IsVisible = true;
    };
    
    
}
