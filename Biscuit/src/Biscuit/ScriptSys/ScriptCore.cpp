#include "pch.h"
#include "ScriptCore.h"

namespace Biscuit
{
    sol::state Biscuit::ScriptCore::lua;
    ScriptCore::ScriptCore()
    {
        lua.open_libraries
        (
            sol::lib::base,
            sol::lib::package,
            sol::lib::string,
            sol::lib::table
        );
        Init();
        
    }

    void ScriptCore::Init()
    {
        lua.new_usertype<Sprite>
        (
            "Sprite",
            "setPos", static_cast<void(Sprite::*)(float,float)>(&Sprite::SetPos),
            "setRot", &Sprite::SetRotation,
            "setScale", &Sprite::SetScale,
            "getPos", &Sprite::GetPos,
            "getRot", &Sprite::GetRotation,
            "getScale", &Sprite::GetScale,
            "setCollidable", &Sprite::SetCollidable,
            "getCollidable", &Sprite::GetCollidable,
            "setVisible", &Sprite::SetVisible,
            "getVisible", &Sprite::GetVisible,
            "getName", &Sprite::GetName,
            "update", &Sprite::Update
        );
    }

    void ScriptCore::BindSpriteObject(std::shared_ptr<Sprite>& obj)
    {
        lua[obj->GetName()] = obj;
    }

    void ScriptCore::BindSpriteObject(Sprite* obj)
    {
        BC_CORE_INFO(obj->GetName());
        lua[obj->GetName()] = obj;
    }

    void ScriptCore::BindLua(const std::string& scriptPath)
    {
        lua.script_file(scriptPath.c_str());
    }

    sol::function ScriptCore::GetLuaMethod(const std::string& table, const std::string& method)
    {
        sol::table _table = lua[table];
        return _table[method];
    }
}
