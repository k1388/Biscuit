#pragma once
#include "Event.h"
#include <sstream>

namespace Biscuit
{
	/// <summary>
	/// 窗口大小更改事件类
	/// </summary>
	class BISCUIT_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(
			unsigned int width,
			unsigned int height
		):m_width(width), m_height(height){}

		inline unsigned int GetWidth() const { return m_width; }
		inline unsigned int GetHeight() const { return m_height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent{W:" << m_width << " H:" << m_height << "}";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_width;
		unsigned int m_height;
	};

	/// <summary>
	/// 窗口关闭事件类
	/// </summary>
	class BISCUIT_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent(){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowCloseEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		
	};



}