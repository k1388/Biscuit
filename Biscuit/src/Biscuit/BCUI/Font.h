#pragma once
#include "imgui.h"

namespace Biscuit
{
    class Application;
}
//class Sandbox;
namespace Biscuit::BCUI
{
    class Font
    {
    public:
        Font(const Font&) = delete;
        Font& operator=(const Font&) = delete;
        std::string GetFontName()
        {
            return m_FontName;
        }
        ImFont* GetFontBySize(int size) const
        {
            if (size <= 1)
            {
                return m_Fonts[1];
            }
            if (size >=100)
            {
                return m_Fonts[100];
            }
            return m_Fonts[size];
        }
        Font(const std::string& fontPath, const std::string name);
    protected:
         //friend class Biscuit::Application;
        //friend class Sandbox;
        
    private:
       
        std::string m_FontPath;
        ImFont* m_Fonts[103];
        bool m_IsInitialized = false;
        std::string m_FontName;
    };

}
