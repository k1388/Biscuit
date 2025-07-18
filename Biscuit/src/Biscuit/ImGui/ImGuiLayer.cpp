#include "pch.h"
#include "ImGuiLayer.h"

namespace Biscuit
{
    ImGuiLayer::ImGuiLayer():Layer("ImGuiLayer")
    {}
    ImGuiLayer::ImGuiLayer(const std::string& name):Layer(name)
    {}
    void ImGuiLayer::OnUpdate()
    {
        // 初始化OpenGL
        ImGui_ImplOpenGL3_NewFrame();
        // 初始化Glfw
        ImGui_ImplGlfw_NewFrame();
        // 初始化imgui
        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(50, 50)); // 示例：位于 (50, 50) 处，从左上角开始
        ImGui::SetNextWindowBgAlpha(0.0f); // 使背景完全透明

        // 开始一个“伪窗口”，带有特定的标志，使其不可见且不可交互
        ImGui::Begin(GetName().c_str(), nullptr,
                     ImGuiWindowFlags_NoTitleBar |           // 移除标题栏
                     ImGuiWindowFlags_NoResize |             // 阻止用户调整大小
                     ImGuiWindowFlags_NoMove |               // 阻止用户移动
                     ImGuiWindowFlags_NoScrollbar |          // 隐藏滚动条
                     ImGuiWindowFlags_NoScrollWithMouse |    // 禁用鼠标滚轮滚动
                     ImGuiWindowFlags_NoCollapse |           // 阻止窗口折叠
                     ImGuiWindowFlags_NoBackground |         // 关键：使背景不可见
                     ImGuiWindowFlags_AlwaysAutoResize |     // 自动调整大小以适应内容
                     ImGuiWindowFlags_NoBringToFrontOnFocus |// 阻止点击时窗口置顶
                     ImGuiWindowFlags_NoNavInputs            // 禁用键盘/手柄导航
        );
        DrawContent();
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event& e)
    {
    
    }

    void ImGuiLayer::OnAttach()
    {
        
    }

    void ImGuiLayer::OnDetach()
    {
    
    }

    void ImGuiLayer::DrawContent()
    {
        
    }
}

