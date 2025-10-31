#include "pch.h"
#include "Input.h"
#include "Application.h"

namespace Biscuit
{
    Input* Input::m_Instance = new Input();
    
    bool Input::IsKeyPressed(int key)
    {
        return m_Instance->IsKeyPressedImpl(key);
    }

    bool Input::IsMouseButtonPressed(int button)
    {
        return m_Instance->IsMouseButtonPressedImpl(button);
    }

    float Input::GetMouseX()
    {
        return m_Instance->GetMouseXImpl();
    }

    float Input::GetMouseY()
    {
        return m_Instance->GetMouseYImpl();
    }

    Vec2 Input::GetMousePosition()
    {
        return m_Instance->GetMousePosImpl();
    }

    Input* Input::GetInstance()
    {
        return m_Instance;
    }

    bool Input::IsKeyPressedImpl(int key)
    {
        auto window = Application::Get()->GetApplicationWindow().GetWindow();
        auto state = glfwGetKey(window, key);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressedImpl(int button)
    {
        auto window = Application::Get()->GetApplicationWindow().GetWindow();
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    float Input::GetMouseXImpl()
    {
        auto window = Application::Get()->GetApplicationWindow().GetWindow();
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return x;
    }

    float Input::GetMouseYImpl()
    {
        auto window = Application::Get()->GetApplicationWindow().GetWindow();
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return y;
    }

    Vec2 Input::GetMousePosImpl()
    {
        auto window = Application::Get()->GetApplicationWindow().GetWindow();
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return Vec2(x, y);
    }
}
