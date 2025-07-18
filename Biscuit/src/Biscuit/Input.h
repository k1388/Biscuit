#pragma once
#include "Math/Vec2.h"
namespace Biscuit
{
    class BISCUIT_API Input
    {
    public:
        static bool IsKeyPressed(int key);
        static bool IsMouseButtonPressed(int button);
        static float GetMouseX();
        static float GetMouseY();
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
