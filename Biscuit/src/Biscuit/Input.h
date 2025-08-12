#pragma once
#include "Math/Vec2.h"
namespace Biscuit
{
    class Input
    {
    public:
        /// <summary>
        /// 获得按键是否按下
        /// </summary>
        /// <param name="key">按键</param>
        /// <returns>是否按下</returns>
        static bool IsKeyPressed(int key);

        /// <summary>
        /// 获得鼠标按键是否按下
        /// </summary>
        /// <param name="key">鼠标按键</param>
        /// <returns>是否按下</returns>
        static bool IsMouseButtonPressed(int button);

        /// <summary>
        /// 获取鼠标X坐标
        /// </summary>
        /// <returns>鼠标X坐标</returns>
        static float GetMouseX();

        /// <summary>
        /// 获取鼠标Y坐标
        /// </summary>
        /// <returns>鼠标Y坐标</returns>
        static float GetMouseY();

        /// <summary>
        /// 获取鼠标坐标
        /// </summary>
        /// <returns>鼠标坐标</returns>
        static Vec2 GetMousePosition();
        
    private:
        bool IsKeyPressedImpl(int key);
        bool IsMouseButtonPressedImpl(int button);
        float GetMouseXImpl();
        float GetMouseYImpl();
        Vec2 GetMousePosImpl();
        
        static Input* m_Instance;
    };
}
