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
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin(GetName().c_str());
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
        ImGui::Button("Button",ImVec2(200,20));
        ImGui::Text("Hello World!");
    }
}

