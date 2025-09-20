#pragma once
#include "Event.h"
#include <sstream>

namespace Biscuit
{
	/// <summary>
	/// 键盘事件类
	/// </summary>
	class KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeybord | EventCategoryInput)

	protected:
		KeyEvent(int keyCode) :m_KeyCode(keyCode) {}

		int m_KeyCode;
	};

	/// <summary>
	/// 按下键盘按键事件类
	/// </summary>
	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount):KeyEvent(keyCode), m_repeatCount(repeatCount){}

		inline int GetRepeatCount() const { return m_repeatCount; }

		std::string ToString() const override 
		{
			std::stringstream ss;
			ss << "KeyPressedEvent{KeyCode:" << m_KeyCode << " RepeatCount:" << m_repeatCount << "}";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_repeatCount;
	};

	/// <summary>
	/// 松开键盘按键事件类
	/// </summary>
	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode):KeyEvent(keyCode){}
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent{KeyCode:" << m_KeyCode << "}";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}