#pragma once
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include "Biscuit/InGame/Sprite.h"

namespace Biscuit
{
    class ScriptCore
    {
    public:
        ScriptCore(const ScriptCore&) = delete;
        ScriptCore& operator=(const ScriptCore&) = delete;

        static sol::state lua;
        inline static bool hasInitialized = false;
        
        ScriptCore();

        void Init();
        static void BindSpriteObject(std::shared_ptr<Sprite>& obj);
        static void BindSpriteObject(Sprite* obj);
        static void BindLua(const std::string& scriptPath);
        static void LoadLua(const std::string& scriptPath);
        static sol::function GetLuaMethod(const std::string& table, const std::string& method);
        static void BindLuaTableToSprite(std::shared_ptr<Sprite> obj);
    };
}
