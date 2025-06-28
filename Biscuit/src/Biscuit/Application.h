#pragma once

#include "Core.h"
#include "Window.h"

namespace Biscuit
{
	/// <summary>
	/// Application是游戏程序的最底层
	/// </summary>
	class BISCUIT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;
	};

	Application* CreateApplication();
}
