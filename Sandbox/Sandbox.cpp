#include "Biscuit.h"

/// <summary>
/// 程序入口main()见src/Biscuit/EntryPoint.h
/// </summary>

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
