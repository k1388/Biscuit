#pragma once

#include "Core.h"
#include "Window.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "LayerStack.h"

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
		void PushOverLay(Layer* overlay);
		void PushLayer(Layer* layer);
		void OnEvent(Event& e);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_IsRunning = true;
		bool OnWindowClose(WindowCloseEvent& e);
		LayerStack m_LayerStack;
	};

	Application* CreateApplication();
}
