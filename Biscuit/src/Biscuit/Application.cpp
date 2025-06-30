#include "pch.h"
#include "Application.h"
#include "GLFW/glfw3.h"


namespace Biscuit
{


	void Application::OnEvent(Event& e) 
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) {return this->OnWindowClose(e); });
		BC_CORE_TRACE("{0}", e.ToString());
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}

	Application::Application()
	{
		if (!glfwInit())
		{
			BC_CORE_ERROR("Failed to init GLFW!");
			return;
		}
		m_Window = std::unique_ptr<Window>(new Window());
		m_Window->SetEventCallback([this](Event& e) {
			this->OnEvent(e);
		});
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_IsRunning)
		{
			glClearColor(0.8, 0.8, 0.8, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
			
		}
	}

}

