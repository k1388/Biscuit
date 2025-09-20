#pragma once
#ifdef BC_PLATFORM_WINDOWS

/// <summary>
/// 此方法由游戏项目定义
/// </summary>
/// <returns>返回指向Application的指针</returns>
extern Biscuit::Application* Biscuit::CreateApplication();

int main(int argc, char** argv)
{
	printf("THE ENTRY POINT\n");
	Biscuit::Log::Init();
	BC_CORE_INFO("Engine Logger Ready");
	BC_INFO("Application Logger Ready");
	
	
	auto app = Biscuit::CreateApplication();
	app->Run();
	delete app;
}

#endif