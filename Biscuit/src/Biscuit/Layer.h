#pragma once
#include <string>
#include "Event/Event.h"

namespace Biscuit
{
	/// <summary>
	/// 在应用程序上的层
	/// </summary>
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer") : m_Name(name) {}
		virtual ~Layer();
		virtual void OnUpdate();
		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnEvent(Event& e);
		inline std::string GetName() const { return m_Name; }
	private:
		std::string m_Name;
	};
}
