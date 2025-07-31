#include "pch.h"
#include "Font.h"

namespace Biscuit::BCUI
{
    Font::Font(const std::string& fontPath, const std::string name)
    {
        ImGuiIO& io = ImGui::GetIO();
        if (io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 13) == NULL)
        {
            for (int i = 1; i <= 100; ++i)
            {
                m_Fonts[i] = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", i);
            }
        }
        else
        {
            for (int i = 1; i <= 100; ++i)
            {
                m_Fonts[i] = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), i);
            }
        }

        m_FontName = name;
        m_IsInitialized = true;
    }
}
