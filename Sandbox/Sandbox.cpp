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
	Sandbox(const Window::WindowProps& props):Application(props){}
	std::shared_ptr<Sprite> drawable = std::make_shared<Sprite>("C:/Users/kanho/OneDrive/Desktop/41903-1859816609.png");
	void OnGameStart() override
	{
		AddSprite(drawable);

		auto UI = new BCUI::BCUI();
		UI->Add(new BCUI::ProgressBar());
		PushOverLay(UI);
	}

	void OnSpriteInited() override
	{
		drawable->AddTexture("C:/Users/kanho/OneDrive/Desktop/7-3-2025_10-52-21_PM.png");
		drawable->OnClick([](Vec2 position)
		{
			BC_INFO("aaa!");
		});
		drawable->OnUpdate([=]()
		{
			float speed = 300;
			if (Input::IsKeyPressed(KEY_W))
			{
				drawable->SetPos(drawable->GetPos() + Vec2(0, -speed * deltaTime));
			}
			if (Input::IsKeyPressed(KEY_A))
			{
				drawable->SetPos(drawable->GetPos() + Vec2(-speed * deltaTime, 0 ));
			}
			if (Input::IsKeyPressed(KEY_S))
			{
				drawable->SetPos(drawable->GetPos() + Vec2(0, speed * deltaTime));
			}
			if (Input::IsKeyPressed(KEY_D))
			{
				drawable->SetPos(drawable->GetPos() + Vec2(speed * deltaTime, 0 ));
			}
		});
	}
};

Biscuit::Application* Biscuit::CreateApplication()
{
	Window::WindowProps* props = new Window::WindowProps("Game",1920,1080);
	return new Sandbox(*props);
}

