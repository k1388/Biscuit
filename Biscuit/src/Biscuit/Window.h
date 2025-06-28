#pragma once
#include "pch.h"
#include "Core.h"
#include "Event/Event.h"
#include "GLFW/glfw3.h"

namespace Biscuit
{
	/// <summary>
	/// 窗口类
	/// </summary>
	class BISCUIT_API Window
	{
	public:

		/// <summary>
		/// 窗口基本属性
		/// </summary>
		struct WindowProps
		{
			std::string Title;
			int			Width;
			int			Height;

			WindowProps
			(
				const std::string title = "Biscuit Engine",
				int width = 1280,
				int height = 720
			) :Title(title), Width(width), Height(height) {}
		};


		using EventCallbackFn = std::function<void(Event&)>;

		~Window()
		{
			ShutDown();
		}

		void OnUpdate()
		{
			glfwPollEvents();	// 处理窗口事件队列
			glfwSwapBuffers(m_Window);	// 交换前后缓冲区指针（将后缓冲区已渲染的图像显示出来）

		}

		int GetWidth()
		{
			return m_Props.Width;
		}

		int GetHeight() 
		{
			return m_Props.Height;
		}

		void SetEventCallback (const EventCallbackFn& callback)
		{
			m_Callback = callback;
		}

		void SetVSync(bool enable)
		{
			m_IsVSync = enable;
			if (m_IsVSync)
			{
				glfwSwapInterval(1);
			}
			else
			{
				glfwSwapInterval(0);
			}
		}

		bool IsVSync()
		{
			return m_IsVSync;
		}

		void ShutDown()
		{
			if (m_Window != nullptr)
			{
				glfwDestroyWindow(m_Window);
			}
		}

		Window(const WindowProps& props = WindowProps())
		{
			m_Window = glfwCreateWindow
			(
				m_Props.Width, m_Props.Height, m_Props.Title.c_str(),
				nullptr, nullptr
			);
			SetVSync(true);
			glfwMakeContextCurrent(m_Window);
		}

	private:
		GLFWwindow *m_Window;
		WindowProps m_Props;
		EventCallbackFn m_Callback;
		bool m_IsVSync;
	};
}