#include "pch.h"
#include "ScriptCore.h"
#include "../Math/Vec4.h"
#include "Biscuit/Input.h"
#include "Biscuit/Keycode.h"
#include "Biscuit/Math/Math.h"

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
        lua.new_usertype<Math>(
            "Math",
            "clamp", &Math::Clamp
        );
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
        table["is_key_pressed"] = &Input::IsKeyPressed;
        table["is_mouse_button_pressed"] = &Input::IsMouseButtonPressed;
        table["get_mouse_x"] = &Input::GetMouseX;
        table["get_mouse_y"] = &Input::GetMouseY;
        table["get_mouse_pos"] = &Input::GetMousePosition;
        lua["Input"] = table;

        sol::table key = lua.create_table();
        REG(KEY_UNKNOWN);
        REG(KEY_SPACE);
        REG(KEY_APOSTROPHE);
        REG(KEY_COMMA);
        REG(KEY_MINUS);
        REG(KEY_PERIOD);
        REG(KEY_SLASH);
        REG(KEY_0);
        REG(KEY_1);
        REG(KEY_2);
        REG(KEY_3);
        REG(KEY_4);
        REG(KEY_5);
        REG(KEY_6);
        REG(KEY_7);
        REG(KEY_8);
        REG(KEY_9);
        REG(KEY_SEMICOLON);
        REG(KEY_EQUAL);
        REG(KEY_A);
        REG(KEY_B);
        REG(KEY_C);
        REG(KEY_D);
        REG(KEY_E);
        REG(KEY_F);
        REG(KEY_G);
        REG(KEY_H);
        REG(KEY_I);
        REG(KEY_J);
        REG(KEY_K);
        REG(KEY_L);
        REG(KEY_M);
        REG(KEY_N);
        REG(KEY_O);
        REG(KEY_P);
        REG(KEY_Q);
        REG(KEY_R);
        REG(KEY_S);
        REG(KEY_T);
        REG(KEY_U);
        REG(KEY_V);
        REG(KEY_W);
        REG(KEY_X);
        REG(KEY_Y);
        REG(KEY_Z);
        REG(KEY_LEFT_BRACKET);
        REG(KEY_BACKSLASH);
        REG(KEY_RIGHT_BRACKET);
        REG(KEY_GRAVE_ACCENT);
        REG(KEY_WORLD_1);
        REG(KEY_WORLD_2);
        REG(KEY_ESCAPE);
        REG(KEY_ENTER);
        REG(KEY_TAB);
        REG(KEY_BACKSPACE);
        REG(KEY_INSERT);
        REG(KEY_DELETE);
        REG(KEY_RIGHT);
        REG(KEY_LEFT);
        REG(KEY_DOWN);
        REG(KEY_UP);
        REG(KEY_PAGE_UP);
        REG(KEY_PAGE_DOWN);
        REG(KEY_HOME);
        REG(KEY_END);
        REG(KEY_CAPS_LOCK);
        REG(KEY_SCROLL_LOCK);
        REG(KEY_NUM_LOCK);
        REG(KEY_PRINT_SCREEN);
        REG(KEY_PAUSE);
        REG(KEY_F1);
        REG(KEY_F2);
        REG(KEY_F3);
        REG(KEY_F4);
        REG(KEY_F5);
        REG(KEY_F6);
        REG(KEY_F7);
        REG(KEY_F8);
        REG(KEY_F9);
        REG(KEY_F10);
        REG(KEY_F11);
        REG(KEY_F12);
        REG(KEY_F13);
        REG(KEY_F14);
        REG(KEY_F15);
        REG(KEY_F16);
        REG(KEY_F17);
        REG(KEY_F18);
        REG(KEY_F19);
        REG(KEY_F20);
        REG(KEY_F21);
        REG(KEY_F22);
        REG(KEY_F23);
        REG(KEY_F24);
        REG(KEY_F25);
        REG(KEY_KP_0);
        REG(KEY_KP_1);
        REG(KEY_KP_2);
        REG(KEY_KP_3);
        REG(KEY_KP_4);
        REG(KEY_KP_5);
        REG(KEY_KP_6);
        REG(KEY_KP_7);
        REG(KEY_KP_8);
        REG(KEY_KP_9);
        REG(KEY_KP_DECIMAL);
        REG(KEY_KP_DIVIDE);
        REG(KEY_KP_MULTIPLY);
        REG(KEY_KP_SUBTRACT);
        REG(KEY_KP_ADD);
        REG(KEY_KP_ENTER);
        REG(KEY_KP_EQUAL);
        REG(KEY_LEFT_SHIFT);
        REG(KEY_LEFT_CONTROL);
        REG(KEY_LEFT_ALT);
        REG(KEY_LEFT_SUPER);
        REG(KEY_RIGHT_SHIFT);
        REG(KEY_RIGHT_CONTROL);
        REG(KEY_RIGHT_ALT);
        REG(KEY_RIGHT_SUPER);
        REG(KEY_MENU);
        REG(KEY_LAST);
        REG(MOUSE_BUTTON_1);
        REG(MOUSE_BUTTON_2);
        REG(MOUSE_BUTTON_3);
        REG(MOUSE_BUTTON_4);
        REG(MOUSE_BUTTON_5);
        REG(MOUSE_BUTTON_6);
        REG(MOUSE_BUTTON_7);
        REG(MOUSE_BUTTON_8);
        REG(MOUSE_BUTTON_LAST);
        REG(MOUSE_BUTTON_LEFT);
        REG(MOUSE_BUTTON_RIGHT);
        REG(MOUSE_BUTTON_MIDDLE);
        lua["key"] = key;
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
        testTbl["sprite"] = obj.get();   // 裸指针

        sol::table mt = lua.create_table();
        mt[sol::meta_function::index] = [](sol::table t, sol::object k) -> sol::object
        {
            return t["sprite"][k];       
        };

        testTbl[sol::metatable_key] = mt;
        lua["test"] = testTbl;
        obj->SetLuaReference(testTbl);
    }
    
}
