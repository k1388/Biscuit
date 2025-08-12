#pragma once
#include "imgui.h"

namespace Biscuit
{
    class Application;
}
//class Sandbox;
namespace Biscuit::BCUI
{
    /// <summary>
    /// 字体类
    /// 该类实际上包含大小1~100的所有某种Imgui字体
    /// 您应该在程序初始化时加载字体
    /// </summary>
    class Font
    {
    public:
        Font(const Font&) = delete;
        Font& operator=(const Font&) = delete;

        /// <summary>
        /// 获取字体名称
        /// </summary>
        /// <returns>字体名称</returns>
        std::string GetFontName()
        {
            return m_FontName;
        }

        /// <summary>
        /// 获取特定大小的字体
        /// </summary>
        /// <param name="size">大小</param>
        /// <returns></returns>
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
       
        std::string     m_FontPath;
        ImFont*         m_Fonts[103];
        bool            m_IsInitialized = false;
        std::string     m_FontName;
    };

}
