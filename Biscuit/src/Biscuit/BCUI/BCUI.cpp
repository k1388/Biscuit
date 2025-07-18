#include <pch.h>
#include "BCUI.h"
namespace Biscuit::BCUI
{
    void BCUI::DrawContent()
    {
        for (auto i : m_Wdgets)
        {
            if (!(i->GetVisible()))
                continue;
            
            ImGui::SetCursorPosX(i->GetPosition().GetX());
            ImGui::SetCursorPosY(i->GetPosition().GetY());
            ImGui::PushID(i->GetName().c_str());
            switch (i->GetWidgetType())
            {
            case Widget::WidgetType::Button:
                {
                    if (
                        ImGui::Button(
                            dynamic_cast<Button*>(i)->GetLabel().c_str(),
                            ImVec2(i->GetSize().GetX(), i->GetSize().GetY())
                        )
                    )
                    {
                        dynamic_cast<Button*>(i)->OnClickEvent();
                    }

                    break;
                }
                    
            case Widget::WidgetType::Label:
                {
                    if (i->GetVisible())
                    ImGui::Text(
                        dynamic_cast<Label*>(i)->GetText().c_str(),
                        ImVec2(i->GetSize().GetX(), i->GetSize().GetY())
                    );
                    break;
                }
            case Widget::WidgetType::Null:
                break;
            default:
                break;
            }
            ImGui::PopID();
        }
    }

    void BCUI::Add(Widget* widget)
    {
        m_Wdgets.push_back(widget);
    }
}
