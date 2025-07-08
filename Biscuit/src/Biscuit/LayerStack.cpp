#include "pch.h"
#include "LayerStack.h"

Biscuit::LayerStack::LayerStack()
{
	m_It = m_LayerVec.begin();
}

Biscuit::LayerStack::~LayerStack()
{
	for(auto i : m_LayerVec)
	{
		delete i;
	}
}

void Biscuit::LayerStack::PushOverlay(Layer* overlay)
{
	m_LayerVec.push_back(overlay);
}

void Biscuit::LayerStack::PushLayer(Layer* layer)
{
	m_LayerVec.emplace(m_It, layer);
}

void Biscuit::LayerStack::PopOverlay(Layer* overlay)
{
	auto it = std::find(m_LayerVec.begin(), m_LayerVec.end(), overlay);
	if (it != m_LayerVec.end())
	{
		m_LayerVec.erase(it);
	}
}

void Biscuit::LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find(m_LayerVec.begin(), m_LayerVec.end(), layer);
	if (it != m_LayerVec.end())
	{
		m_LayerVec.erase(it);
		m_It--;
	}
}
