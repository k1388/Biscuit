#pragma once
#include "Biscuit/ImGui/ImGuiLayer.h"
#include "Widget.h"
#include "Label.h"
#include "Button.h"
#include "ProgressBar.h"

namespace Biscuit::BCUI
{
    /// <summary>
    /// UI层，调用PushOverlay从而显示该层
    /// </summary>
    class BCUI : public ImGuiLayer
    {
    public:
        void DrawContent() override;

        /// <summary>
        /// 在本层附加BCUI组件
        /// </summary>
        /// <param name="widget">组件</param>
        void Add(Widget* widget);
    private:
        std::vector<Widget*>    m_Wdgets;
    };
}
