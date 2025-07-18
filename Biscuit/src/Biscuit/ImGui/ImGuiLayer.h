#pragma once
#include "Biscuit/Layer.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "../BCUI/Widget.h"
#include "../BCUI/Button.h"

namespace Biscuit
{
/// <summary>
/// ImGui图层，将来应该再封装一层成为UI类 --7.9 \n
/// 已封装为BCUI类 --7.10
/// </summary>
class BISCUIT_API ImGuiLayer : public Layer
{
public:
    ImGuiLayer();
    ImGuiLayer(const std::string& name);

    /// <summary>
    /// 刷新ImGui（包括渲染）
    /// </summary>
    void OnUpdate() override;

    void OnEvent(Event& e) override;
    void OnAttach() override;
    void OnDetach() override;

    /// <summary>
    /// 绘制ImGui内容
    /// </summary>
    virtual void DrawContent();
    
};
    
}
