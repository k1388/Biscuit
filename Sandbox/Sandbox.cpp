#include "Biscuit.h"
#include "Biscuit/BCUI/BCUI.h"
#include "Biscuit/BCUI/Label.h"

using namespace Biscuit;
/// <summary>
/// 程序入口main()见src/Biscuit/EntryPoint.h
/// </summary>


class Sandbox : public Biscuit::Application
{
public:
	void OnGameStart() override
	{
		Sprite *drawable = new Sprite("C:/Users/kanho/OneDrive/Desktop/41903-1859816609.png");
		AddSprite(drawable);
	}
};

Biscuit::Application* Biscuit::CreateApplication()
{
	return new Sandbox();
}

