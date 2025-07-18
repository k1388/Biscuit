#include "pch.h"
#include "LayerStack.h"
namespace Biscuit
{
	LayerStack::LayerStack()
	{
		m_It = m_LayerVec.begin();
	}

	LayerStack::~LayerStack()
	{
		for(auto i : m_LayerVec)
		{
			delete i;
		}
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_LayerVec.push_back(overlay);
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerVec.emplace(m_It, layer);
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_LayerVec.begin(), m_LayerVec.end(), overlay);
		if (it != m_LayerVec.end())
		{
			m_LayerVec.erase(it);
		}
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_LayerVec.begin(), m_LayerVec.end(), layer);
		if (it != m_LayerVec.end())
		{
			m_LayerVec.erase(it);
			m_It--;
		}
	}

}
