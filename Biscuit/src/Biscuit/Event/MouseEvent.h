#pragma once
#include "Event.h"
#include <sstream>

namespace Biscuit
{
	/// <summary>
	/// 鼠标移动事件类
	/// </summary>
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y):m_X(x),m_Y(y){}

		inline float GetMouseX() const { return m_X; }
		inline float GetMouseY() const { return m_Y; }

		std::string ToString() const override 
		{
			std::stringstream ss;
			ss << "MouseMovedEvent{x:" << m_X << " y:" << m_Y << "}";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

	private:
		double m_X;
		double m_Y;
	};

	/// <summary>
	/// 鼠标滚轮滚动事件类
	/// </summary>
	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}
		
		inline float GetOffsetX() const { return m_XOffset; }
		inline float GetOffsetY() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent{offsetX:" << m_XOffset << " offsetY:" << m_YOffset << "}";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

	private:
		float m_XOffset;
		float m_YOffset;
	};

	/// <summary>
	/// 鼠标点击事件类
	/// </summary>
	class MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)
	protected:
		MouseButtonEvent(int button) :m_Button(button) {}

		int m_Button;
	};

	/// <summary>
	/// 鼠标按键按下事件类
	/// </summary>
	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button):MouseButtonEvent(button){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MousePressedEvent{mouseButton:" << m_Button << "}";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	/// <summary>
	/// 鼠标按键松开事件类
	/// </summary>
	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) :MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseReleasedEvent{mouseButton:" << m_Button << "}";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}