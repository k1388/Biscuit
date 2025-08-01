#include "pch.h"
#include "Application.h"

#include "GlobalResources.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "Input.h"
#include "ImGui/ImGuiLayer.h"
#include "InGame/Sprite.h"

namespace Biscuit
{
	Application* Application::m_Instance = nullptr;
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

	Window& Application::GetApplicationWindow() const
	{
		return *m_Window;
	}

	Application* Application::Get()
	{
		return m_Instance;
	}

	void Application::AddSprite(std::shared_ptr<Sprite> sprite)
	{
		m_SpriteLayer->AddSprite(sprite);
	}

	void Application::RemoveSprite(std::shared_ptr<Sprite> sprite)
	{
		m_SpriteLayer->RemoveSprite(sprite);
	}

	void Application::LoadFontFromFile(const std::string& filePath, const std::string& name)
	{
		UIFonts.push_back(std::make_shared<BCUI::Font>(filePath, name));
	}

	void Application::LoadTextureFromFile(const std::string& filePath, const std::string& name)
	{

		Textures.push_back(std::make_shared<Texture>(filePath, name));
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}

	bool Application::InitGLFW()
	{
		// 初始化GLFW
		if (!glfwInit())
		{
			BC_CORE_ERROR("Failed to init GLFW!");
			return false;
		}

		// 调整OpenGL版本为3.3，启用核心模式渲染
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		return true;
	}

	void Application::InitImGuiAndGL()
	{
		// 初始化ImGui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext(nullptr);
		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontDefault();
		(void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(m_Window->GetWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 410");
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // 标准的混合函数

		
	}


	Application::Application()
	{
		if (!InitGLFW())
		{
			return;
		}
		m_Window = std::unique_ptr<Window>(new Window());
		m_Window->SetEventCallback([this](Event& e) {
			this->OnEvent(e);
		});
		InitImGuiAndGL();
		m_Instance = this;
	}

	Application::~Application()
	{
	}

	Application::Application(Window::WindowProps windowProperty)
	{
		if (!InitGLFW())
		{
			return;
		}
		m_Window = std::unique_ptr<Window>(new Window(windowProperty));
		m_Window->SetEventCallback([this](Event& e) {
			this->OnEvent(e);
		});
		InitImGuiAndGL();
		m_Instance = this;
		
	}

	void Application::Run()
	{
		m_SpriteLayer = std::make_shared<SpriteLayer>();
		this->PushLayer(m_SpriteLayer.get());

		OnGameStart();
		m_SpriteLayer->InitAllSprites();
		OnSpriteInited();
		
		m_LastFrameTime = glfwGetTime();
		while (m_IsRunning)
		{
			m_CurrentFrameTime = glfwGetTime();
			deltaTime = (m_CurrentFrameTime - m_LastFrameTime);
			m_LastFrameTime = m_CurrentFrameTime;
			OnUpdate();
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.8f, 0.8f, 0.9f, 1);
			//drawable.Draw();
			//drawable.SetPos(drawable.GetPos().GetX()+deltaTime*100, drawable.GetPos().GetY());


			if (Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				m_SpriteLayer->CheckMouseCollisions(Vec2(Input::GetMouseX(), Input::GetMouseY()));
			}

			m_SpriteLayer->CheckAllCollisions();
			
			// 遍历图层栈并更新每一图层
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}
			
			// 交换前后缓冲区，刷新画面
			glfwSwapBuffers(m_Window->GetWindow());
			// 更新glfw事件
			glfwPollEvents();
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

