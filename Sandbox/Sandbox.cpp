#include "Biscuit.h"

using namespace Biscuit;

class Sandbox : public Application
{
public:
	Sandbox(const Window::WindowProps& props):Application(props){}

	std::shared_ptr<Sprite> testSprite;
	std::shared_ptr<BCUI::Button> testUI = std::make_shared<BCUI::Button>();

	void OnInit() override
	{
		auto ui = new BCUI::BCUI();

		LoadTextureFromFile("C:/Users/kanho/OneDrive/Desktop/7-3-2025_10-52-21_PM.png", "tex1");
		testSprite = std::make_shared<Sprite>(GetTexture("tex1"));
		testSprite->SetRotation(90);
		AddSprite(testSprite);
		PushOverLay(ui);
	}
};

Application* Biscuit::CreateApplication()
{
	Window::WindowProps* props = new Window::WindowProps("Game", 1920, 1080);
	return new Sandbox(*props);
}

