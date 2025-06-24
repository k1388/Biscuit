#pragma once
#include "Event.h"
#include <sstream>

namespace Biscuit
{
	class BISCUIT_API MouseMovedEvent : public Event
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
		float m_X;
		float m_Y;
	};

	class BISCUIT_API MouseScrolledEvent : public Event
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

	class BISCUIT_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)
	protected:
		MouseButtonEvent(int button) :m_Button(button) {}

		int m_Button;
	};

	class BISCUIT_API MouseButtonPressedEvent : public MouseButtonEvent
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

	class BISCUIT_API MouseButtonReleasedEvent : public MouseButtonEvent
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