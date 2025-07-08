#pragma once
#include "Biscuit/Layer.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace Biscuit
{
class BISCUIT_API ImGuiLayer : public Layer
{
public:
    ImGuiLayer();
    ImGuiLayer(const std::string& name);
    void OnUpdate() override;
    void OnEvent(Event& e) override;
    void OnAttach() override;
    void OnDetach() override;
    virtual void DrawContent();
};
    
}
