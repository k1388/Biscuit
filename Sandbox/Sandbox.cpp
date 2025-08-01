#include "Biscuit.h"

using namespace Biscuit;

class Sandbox : public Application
{
public:
	Sandbox(const Window::WindowProps& props):Application(props){}

	void OnInit() override
	{
		LoadFontFromFile("C:\\Windows\\Fonts\\Impact.ttf","Impact");
	}
	
	void OnGameStart() override
	{
		auto ui = new BCUI::BCUI();
		
		auto label = new BCUI::Label(Vec2(400,320),Vec2(400,100));
		label->SetText("Label");
		label->SetLabelFont(GetFont("Impact"), 42);
		
		auto button = new BCUI::Button(Vec2(500,300),Vec2(400,100));
		button->SetLabelFont(GetFont("Impact"), 20);
		button->OnClick([]()
		{
			BC_TRACE("Clicked!");
		});
		
		ui->Add(label);
		ui->Add(button);
		PushOverLay(ui);
	}
};

Biscuit::Application* Biscuit::CreateApplication()
{
	Window::WindowProps* props = new Window::WindowProps("Game",1920,1080);
	return new Sandbox(*props);
}

