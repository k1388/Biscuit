#pragma once
#include "Core.h"
#include "Layer.h"
#include <vector>
namespace Biscuit
{
	class BISCUIT_API LayerStack
	{
	public:
		/// <summary>
		/// 生成LayerStack，将迭代器指向Stack.being()
		/// </summary>
		LayerStack();

		/// <summary>
		/// 销毁LayerStack和其中的内容
		/// </summary>
		~LayerStack();
		using LayerVec = std::vector<Layer*>;
		LayerVec::iterator begin() { return m_LayerVec.begin(); }
		LayerVec::iterator end() { return m_LayerVec.end(); }

		/// <summary>
		/// Push一个遮盖层
		/// </summary>
		/// <param name="overlay">遮盖层</param>
		void PushOverlay(Layer* overlay);

		/// <summary>
		/// Push一个图层
		/// </summary>
		/// <param name="layer">图层</param>
		void PushLayer(Layer* layer);

		/// <summary>
		/// 按指针Pop一个遮盖层
		/// </summary>
		/// <param name="overlay">遮盖层</param>
		void PopOverlay(Layer* overlay);

		/// <summary>
		/// 按指针Pop一个图层
		/// </summary>
		/// <param name="layer">图层</param>
		void PopLayer(Layer* layer);
	private:
		LayerVec m_LayerVec;
		LayerVec::iterator m_It;
	};
}
