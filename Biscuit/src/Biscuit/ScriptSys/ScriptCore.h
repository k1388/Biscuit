#pragma once
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include "Biscuit/InGame/Sprite.h"

namespace Biscuit
{
    /// <summary>
    /// Lua脚本系统，进行Lua系统的绑定和加载等
    /// </summary>
    class ScriptCore
    {
    public:
        ScriptCore(const ScriptCore&) = delete;
        ScriptCore& operator=(const ScriptCore&) = delete;

        static sol::state lua;
        inline static bool hasInitialized = false;
        
        ScriptCore();
        
        /// <summary>
        /// 初始化Lua脚本系统
        /// </summary>
        void Init();

        static void BindSpriteObject(std::shared_ptr<Sprite>& obj);

        static void BindSpriteObject(Sprite* obj);

        /// <summary>
        /// 从路径中加载Lua脚本
        /// 同 LoadLua()
        /// </summary>
        /// <param name="scriptPath">Lua脚本路径</param>
        static void BindLua(const std::string& scriptPath);

        /// <summary>
        /// 从路径中加载Lua脚本
        /// 同BindLua()
        /// </summary>
        /// <param name="scriptPath">Lua脚本路径</param>
        static void LoadLua(const std::string& scriptPath);

        /// <summary>
        /// 从Lua表中获得方法
        /// </summary>
        /// <param name="table">Lua表</param>
        /// <param name="method">方法名</param>
        /// <returns>sol函数</returns>
        static sol::function GetLuaMethod(const std::string& table, const std::string& method);

        /// <summary>
        /// 创建一个表，该表名称与obj所指Spirte的Name相同；
        /// 使Sprite获得该表的引用。
        /// 使Lua脚本支持形如self.Sprite:xxx()的调用
        /// </summary>
        /// <param name="obj"></param>
        static void BindLuaTableToSprite(std::shared_ptr<Sprite> obj);
    };
}
