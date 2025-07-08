#include "pch.h"
#include "Application.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "ImGui/ImGuiLayer.h"

namespace Biscuit
{


	void Application::OnEvent(Event& e) 
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e) {return this->OnWindowClose(e); });
		//BC_CORE_TRACE("{0}", e.ToString());

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if(e.m_Handled)
			{
				break;
			}
		}
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
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
		m_Window = std::unique_ptr<Window>(new Window());
		m_Window->SetEventCallback([this](Event& e) {
			this->OnEvent(e);
		});
		IMGUI_CHECKVERSION();
		ImGui::CreateContext(nullptr);
		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		
		while (m_IsRunning)
		{
			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.8, 0.8, 0.8, 1);
			
			
			// glClear(GL_COLOR_BUFFER_BIT);
			
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}
			glfwSwapBuffers(m_Window->GetWindow());
		}
	}

	void Application::PushOverLay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

}

