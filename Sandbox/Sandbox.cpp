#include "Biscuit.h"
#include "Biscuit/BCUI/BCUI.h"
#include "Biscuit/BCUI/Label.h"

using namespace Biscuit;
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


class Sandbox : public Biscuit::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Biscuit::Application* Biscuit::CreateApplication()
{
	return new Sandbox();
}

