#pragma once
#include "pch.h"
#include "Event/Event.h"
#include "GLFW/glfw3.h"
#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "Glad/glad.h"
namespace Biscuit
{
	/// <summary>
	/// 窗口类
	/// </summary>
	class Window
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
			//glfwPollEvents();	// 处理窗口事件队列
			//glfwSwapBuffers(m_Window);	// 交换前后缓冲区指针（将后缓冲区已渲染的图像显示出来）

		}

		/// <summary>
		/// 获取窗口宽度
		/// </summary>
		/// <returns>返回窗口宽度</returns>
		int GetWidth()
		{
			return m_Props.Width;
		}

		/// <summary>
		/// 获得窗口高度
		/// </summary>
		/// <returns>返回窗口高度</returns>
		int GetHeight() 
		{
			return m_Props.Height;
		}

		/// <summary>
		/// 设置窗口回调函数
		/// </summary>
		/// <param name="callback"></param>
		void SetEventCallback (const EventCallbackFn& callback)
		{
			m_Callback = callback;
		}

		/// <summary>
		/// 设置窗口垂直同步
		/// </summary>
		/// <param name="enable">是否开启垂直同步</param>
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

		/// <summary>
		/// 获取窗口是否垂直同步
		/// </summary>
		/// <returns>返回窗口是否垂直同步</returns>
		bool IsVSync()
		{
			return m_IsVSync;
		}

		/// <summary>
		/// 关闭窗口
		/// </summary>
		void ShutDown()
		{
			if (m_Window != nullptr)
			{
				glfwDestroyWindow(m_Window);
			}
		}

		/// <summary>
		/// 初始化一个窗口
		/// </summary>
		/// <param name="props">窗口基本属性</param>
		Window(const WindowProps& props = WindowProps())
		{
			m_Props = props;
			m_Window = glfwCreateWindow
			(
				m_Props.Width, m_Props.Height, m_Props.Title.c_str(),
				nullptr, nullptr
			);
			SetVSync(true);
			glfwMakeContextCurrent(m_Window);
			int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			glfwSetWindowUserPointer(m_Window, this);

			// 设置窗口调整大小的回调
			glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
				Window& w = *(Window*)glfwGetWindowUserPointer(window);
				w.m_Props.Width = width;
				w.m_Props.Height = height;
				
				WindowResizeEvent event(width, height);
				w.m_Callback(event);
			});

			// 设置关闭窗口的回调
			glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) 
			{
				Window& w = *(Window*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				w.m_Callback(event);
			});

			// 设置键盘按键的回调
			glfwSetKeyCallback
			(
				m_Window, 
				[](GLFWwindow* window, int key, int scancode, int action, int mods
			) 
			{
				Window& w = *(Window*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						w.m_Callback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						w.m_Callback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						w.m_Callback(event);
						break;
					}
				}
			}
			);

			// 设置鼠标按键的回调
			glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
					Window& w = *(Window*)glfwGetWindowUserPointer(window);

					switch (action)
					{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						w.m_Callback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						w.m_Callback(event);
						break;
					}
					}
				}
			);

			// 设置鼠标滚轮的回调
			glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) 
			{
				Window& w = *(Window*)glfwGetWindowUserPointer(window);
				
				MouseScrolledEvent event(xoffset, yoffset);
				w.m_Callback(event);
			}
			);

			// 设置鼠标移动的回调
			glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) 
			{
				Window& w = *(Window*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event(xpos, ypos);
				w.m_Callback(event);
			}
			);
		}

		GLFWwindow* GetWindow() const
		{
			return m_Window;
		}
	private:
		GLFWwindow *m_Window;
		WindowProps m_Props;
		EventCallbackFn m_Callback;
		bool m_IsVSync;
	};
}