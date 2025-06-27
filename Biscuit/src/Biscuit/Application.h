#pragma once

#include "Core.h"

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
	};

	Application* CreateApplication();
}
