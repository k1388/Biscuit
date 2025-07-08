#pragma once
#include "Core.h"
#include "Layer.h"
#include <vector>
namespace Biscuit
{
	class BISCUIT_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		using LayerVec = std::vector<Layer*>;
		LayerVec::iterator begin() { return m_LayerVec.begin(); }
		LayerVec::iterator end() { return m_LayerVec.end(); }
		void PushOverlay(Layer* overlay);
		void PushLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
	private:
		LayerVec m_LayerVec;
		LayerVec::iterator m_It;
	};
}
