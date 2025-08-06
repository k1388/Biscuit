#pragma once

#include "Window.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "LayerStack.h"
#include "SpriteLayer.h"

namespace Biscuit
{
	namespace BCUI
	{
		class Font;
	}

	class BCUI::Font;

	/// <summary>
	/// Application是游戏程序的最底层
	/// </summary>
	class Application
	{
	public:
		Application();
		virtual ~Application();
		Application(Window::WindowProps windowProperty);
		void Run();

		/// <summary>
		/// push一个遮盖层
		/// </summary>
		/// <param name="overlay">遮盖层</param>
		void PushOverLay(Layer* overlay);

		/// <summary>
		/// push一个图层
		/// </summary>
		/// <param name="layer">图层</param>
		void PushLayer(Layer* layer);
		void OnEvent(Event& e);

		Window& GetApplicationWindow() const;

		static Application* Get();

		double deltaTime = 0.0f;

		inline std::shared_ptr<SpriteLayer> GetSpriteLayer() const
		{
			return m_SpriteLayer;
		}

		void AddSprite(std::shared_ptr<Sprite> sprite);

		void RemoveSprite(std::shared_ptr<Sprite> sprite);

		static void LoadFontFromFile(const std::string& filePath, const std::string& name);

		static void LoadTextureFromFile(const std::string& filePath, const std::string& name);
		
		/// <summary>
		/// 游戏开始运行时会调用这个方法
		/// 一般来说，该方法中应该调用AddSprite方法等将Sprite添加至场景
		/// 注意不要在此方法中调用AddTexture以及相关的方法
		/// </summary>
		virtual void OnGameStart() {}
		virtual void OnSpriteInited() {}
		virtual void OnUpdate() {}
		virtual void OnInit() {}
	private:
		/// <summary>
		/// 应用对应的Window类(注意是对GLFWWindow的封装，获得渲染窗口调用m_window->GetWindow())
		/// </summary>
		std::unique_ptr<Window> m_Window;

		/// <summary>
		/// 控制引擎循环
		/// </summary>
		bool m_IsRunning = true;

		bool OnWindowClose(WindowCloseEvent& e);
		LayerStack m_LayerStack;	// 如果将来有Level或者Scene的概念，图层栈应该放到那里面 --7.9

		std::shared_ptr<SpriteLayer> m_SpriteLayer;
		static Application* m_Instance;

		double m_LastFrameTime = 0.0f;
		double m_CurrentFrameTime = 0.0f;

		bool InitGLFW();
		void InitImGuiAndGL();
	};

	Application* CreateApplication();
}
