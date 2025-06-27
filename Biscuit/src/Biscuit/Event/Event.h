#pragma once
#include "../Core.h"
#include <string>
#include <functional>

namespace Biscuit
{
	
	/// <summary>
	/// 所有事件类型的枚举类(有部分未实现)
	/// </summary>
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		WindowMinimize, WindowMaximize,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, 
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
	};

	/// <summary>
	/// 事件分类枚举
	/// </summary>
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeybord		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

// 每个最终子事件类都要使用该宏
#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType(){return EventType::##type;}\
								virtual EventType GetEventType()const override {return GetStaticType();}\
								virtual const char* GetName() const override {return #type;}

// 该宏提供了获得事件分类的虚函数
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}

	/// <summary>
	/// 所有事件的抽象类
	/// </summary>
	class BISCUIT_API Event
	{
	public:
		/// <summary>
		/// 获得自身的事件类型
		/// </summary>
		/// <returns>返回一个事件类型枚举</returns>
		virtual EventType GetEventType() const = 0;

		/// <summary>
		/// 获得事件名称
		/// </summary>
		/// <returns>返回事件名称字符串</returns>
		virtual const char* GetName() const = 0;

		/// <summary>
		/// 获得事件分类
		/// </summary>
		/// <returns>返回一个整数，需要使用EventCategory枚举的掩码解析</returns>
		virtual int GetCategoryFlags() const = 0;

		/// <summary>
		/// 获得事件的描述信息
		/// </summary>
		/// <returns>返回事件字符串</returns>
		virtual std::string ToString() const { return GetName(); }

		inline bool isInCategory(EventCategory cate)
		{
			return GetCategoryFlags() & cate;
		}

	protected:

		/// <summary>
		/// 事件是否已经被处理
		/// </summary>
		bool m_Handled = false;
	};

	/// <summary>
	/// 事件分发器
	/// </summary>
	class EventDispatcher
	{
		/// <summary>
		/// 包装回调函数，其返回值为bool，接受事件T作为参数
		/// </summary>
		template<typename T>
		using EventFn = std::function<bool<T&>>;
	public:
		/// <summary>
		/// 构造事件分发器
		/// </summary>
		/// <param name="e">待分发的事件</param>
		EventDispatcher(Event& e):m_Event(e){}

		/// <summary>
		/// 分发事件
		/// </summary>
		/// <typeparam name="T">事件（Event）类型</typeparam>
		/// <param name="func">事件分发器的回调函数</param>
		/// <returns>返回事件是否被本层处理</returns>
		template<typename T>
		bool Dispatch(EventFn<T&> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator << (std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}