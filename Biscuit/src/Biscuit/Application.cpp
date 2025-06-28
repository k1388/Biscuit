#include "pch.h"
#include "Application.h"
#include "GLFW/glfw3.h"

namespace Biscuit
{

	Application::Application()
	{
		if (!glfwInit())
		{
			BC_CORE_ERROR("Failed to init GLFW!");
			return;
		}
		m_Window = std::unique_ptr<Window>(new Window());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_IsRunning)
		{
			glClearColor(0.5, 0.5, 0.5, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
			
		}
	}

}

