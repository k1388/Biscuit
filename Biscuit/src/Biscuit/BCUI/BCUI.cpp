#include <pch.h>
#include "BCUI.h"

#include "ProgressBar.h"

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
                    auto widget = dynamic_cast<Button*>(i);
                    Vec4 color = widget->GetColor();
                    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, widget->GetFrameRounding());
                    ImGui::PushStyleColor(ImGuiCol_Button,ImVec4
                        (
                        color.X(),
                        color.Y(),
                        color.Z(),
                        color.W())
                        );
                    ImFont* font = widget->GetLabelFont();
                    bool hasFont = false;
                    if (font != NULL)
                    {
                        ImGui::PushFont(font);
                        hasFont = true;
                    }
                    bool pressed = ImGui::Button
                    (
                        widget->GetLabel().c_str(),
                        ImVec2(i->GetSize().GetX(), i->GetSize().GetY())
                    );
                    if (hasFont)
                    {
                        ImGui::PopFont();
                    }
                    ImGui::PopStyleColor(1);
                    ImGui::PopStyleVar(1);
                    if (pressed)
                    {
                        widget->OnClickEvent();
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
            case Widget::WidgetType::ProgressBar:
                {
                    ImGui::ProgressBar
                    (
                    dynamic_cast<ProgressBar*>(i)->GetPercentage(),
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
