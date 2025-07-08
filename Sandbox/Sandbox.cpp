#include "Biscuit.h"

/// <summary>
/// 程序入口main()见src/Biscuit/EntryPoint.h
/// </summary>


class MyLayer : public Biscuit::Layer
{
public:
	MyLayer() :Layer("Mylayer!!!!!") {}
	void OnUpdate() override
	{
		//BC_INFO("game updated");
	}

	void OnEvent(Biscuit::Event& e) override
	{
		//BC_INFO("{0}", e.ToString());
	}
};

class MyUI : public Biscuit::ImGuiLayer
{
public:
	
	// void DrawContent() override
	// {
	// 	ImGui::Button("Button",ImVec2(200,20));
	// }
};

class Sandbox : public Biscuit::Application
{
public:
	Sandbox()
	{
		//PushLayer(new MyLayer());
		PushOverLay(new Biscuit::ImGuiLayer("The UI"));
	}

	~Sandbox()
	{

	}
};

Biscuit::Application* Biscuit::CreateApplication()
{
	return new Sandbox();
}

