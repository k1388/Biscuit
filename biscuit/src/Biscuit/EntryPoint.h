#pragma once
#ifdef BC_PLATFORM_WINDOWS

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