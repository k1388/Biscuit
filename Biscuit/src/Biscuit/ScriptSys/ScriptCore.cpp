#include "pch.h"
#include "ScriptCore.h"
#include "../Math/Vec4.h"

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

        lua.new_usertype<Vec2>
        (
            "Vec2",
            sol::call_constructor,   // 打开“表可调用”语法
            sol::constructors<Vec2(), Vec2(float,float)>(),
            "x", sol::property(&Vec2::GetX, &Vec2::SetX),  // 读写
            "y", sol::property(&Vec2::GetY, &Vec2::SetY),
            //sol::meta_function::to_string, &Vec2::ToString,
            
            sol::meta_function::addition, &Vec2::operator+,
            sol::meta_function::subtraction, &Vec2::operator-
        );

        lua.new_usertype<Vec3>
        (
            "Vec3",
            sol::call_constructor,
            sol::constructors<Vec3(), Vec3(float,float,float)>(),
            "x", sol::property(&Vec3::GetX, &Vec3::SetX),
            "y", sol::property(&Vec3::GetY, &Vec3::SetY),
            "z", sol::property(&Vec3::GetZ, &Vec3::SetZ),
            //sol::meta_function::to_string, &Vec3::ToString,
            
            sol::meta_function::addition, &Vec3::operator+,
            sol::meta_function::subtraction, &Vec3::operator-
        );

        lua.new_usertype<Vec4>
        (
            "Vec4",
            sol::call_constructor,
            sol::constructors<Vec4(), Vec4(float,float,float,float)>(),
            "x", sol::property(&Vec4::GetX, &Vec4::SetX),
            "y", sol::property(&Vec4::GetY, &Vec4::SetY),
            "z", sol::property(&Vec4::GetZ, &Vec4::SetZ),
            "w", sol::property(&Vec4::GetW, &Vec4::SetW),
            //sol::meta_function::to_string, &Vec4::ToString,

            sol::meta_function::addition, &Vec4::operator+,
            sol::meta_function::subtraction, &Vec4::operator-
        );
        
        sol::usertype<Sprite> sprite_type = lua.new_usertype<Sprite>
        (
            "Sprite",
            "set_pos", sol::overload(
                static_cast<void(Sprite::*)(Vec3)>(&Sprite::SetPos),
                static_cast<void(Sprite::*)(float,float)>(&Sprite::SetPos)
            ),
            "set_rot", &Sprite::SetRotation,
            "set_scale", &Sprite::SetScale,
            "get_pos", &Sprite::GetPos,
            "get_rot", &Sprite::GetRotation,
            "get_scale", &Sprite::GetScale,
            "set_collidable", &Sprite::SetCollidable,
            "get_collidable", &Sprite::GetCollidable,
            "set_visible", &Sprite::SetVisible,
            "get_visible", &Sprite::GetVisible,
            "get_name", &Sprite::GetName
            
        );
        sprite_type[sol::meta_function::new_index] = [](sol::table usertype_table, sol::object key, sol::object value) {
            // 允许动态添加字段，存储在 usertype 的 Lua 环境中
            sol::state_view lua(usertype_table.lua_state());
            sol::table env = lua.create_table(); // 或者从 usertype 获取环境表
            env[key] = value;
        };
        sol::table table = lua.create_table();
        lua["Input"] = table;
    }

    void ScriptCore::BindSpriteObject(std::shared_ptr<Sprite>& obj)
    {
        lua[obj->GetName()] = obj;
    }

    void ScriptCore::BindSpriteObject(Sprite* obj)
    {
        //BC_CORE_INFO(obj->GetName());
        lua[obj->GetName()] = obj;
    }

    void ScriptCore::BindLua(const std::string& scriptPath)
    {
        lua.script_file(scriptPath.c_str());
    }

    void ScriptCore::LoadLua(const std::string& scriptPath)
    {
        lua.script_file(scriptPath.c_str());
    }

    sol::function ScriptCore::GetLuaMethod(const std::string& table, const std::string& method)
    {
        sol::table _table = lua[table];
        return _table[method];
    }

    void ScriptCore::BindLuaTableToSprite(std::shared_ptr<Sprite> obj)
    {
        sol::table testTbl = lua.create_table();
        testTbl["sprite"] = obj.get();   // 裸指针即可

        sol::table mt = lua.create_table();
        mt[sol::meta_function::index] = [](sol::table t, sol::object k) -> sol::object
        {
            return t["sprite"][k];       // 自动回落到 Sprite userdata
        };

        testTbl[sol::metatable_key] = mt;
        lua["test"] = testTbl;
        obj->SetLuaReference(testTbl);
    }
    
}
