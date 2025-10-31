#include "pch.h"
#include "Sprite.h"
#include "../ScriptSys/ScriptCore.h"
#include "Biscuit/Application.h"

namespace Biscuit
{
    void Sprite::InOnAttachedToScene()
    {
        if (m_luaRef.valid())
        {
            sol::table self_table = (sol::table)m_luaRef;
            if (self_table.valid())
            {
                sol::object update_obj = self_table["on_attached"]; 
                if (update_obj.valid() && update_obj.is<sol::function>())
                {
                    sol::function update_func = update_obj.as<sol::function>();
                    update_func(self_table);
                    return; 
                }
            }
        }
        if (m_OnAttachedToScene != nullptr)
        {
            m_OnAttachedToScene();
        }
    
    }

    Sprite::Sprite(const std::string& picSrc) : Drawable(picSrc)
    {
        const float sw = float(Application::Get()->GetApplicationWindow().GetWidth());
        const float sh = float(Application::Get()->GetApplicationWindow().GetHeight());

        m_Pos = Vec2(sw/2,sh/2);
        m_OriginalPicSrc = picSrc;
        //Application::Get()->GetSpriteLayer()->AddSprite(this);
        m_luaTable = std::make_shared<LuaTable>();
    }

    Sprite::Sprite(const std::shared_ptr<Texture>& texture): Drawable(texture)
    {
        const float sw = float(Application::Get()->GetApplicationWindow().GetWidth());
        const float sh = float(Application::Get()->GetApplicationWindow().GetHeight());

        m_Pos = Vec2(sw/2,sh/2);
        //m_OriginalPicSrc = picSrc;
        m_luaTable = std::make_shared<LuaTable>();
    }

    void Sprite::BindScript(const std::string& scriptPath)
    {
        ScriptCore::BindSpriteObject(this);
        ScriptCore::BindLua(scriptPath);
        m_bindedLua = true;
        auto _update =  std::make_shared<sol::function>(ScriptCore::GetLuaMethod(m_Name, "update"));
        m_Callback = [_update]()
        {
            (*_update)();
        };
    }

    void Sprite::BindLuaTable(const sol::table& table)
    {
        m_luaTable->table = table;
    }

    sol::table Sprite::GetLuaTable() const
    {
        return m_luaTable->table;
    }

    void Sprite::SetLuaReference(const sol::reference& ref)
    {
        m_luaRef = ref;
    }

    sol::reference Sprite::GetLuaReference() const
    {
        return m_luaRef;
    }

    float* Sprite::CoordTransform()
    {
        const float sw = float(Application::Get()->GetApplicationWindow().GetWidth());
        const float sh = float(Application::Get()->GetApplicationWindow().GetHeight());

        const float w = m_CurTexture->picWidth  * m_Scale * 0.5f;
        const float h = m_CurTexture->picHeight * m_Scale * 0.5f;

        // 顺序：左上、右上、右下、左下
        float corners[4][2] = {
            { -w,  h },   
            {  w,  h }, 
            {  w, -h }, 
            { -w, -h }  
        };

        const float* m = GenerateRotateMatrix(); 
        const float  c = m[0], s = m[1];

        for (int i = 0; i < 4; ++i)
        {
            float x = corners[i][0];
            float y = corners[i][1];

            float rx = c * x - s * y;
            float ry = s * x + c * y;

            rx += m_Pos.GetX();
            ry += m_Pos.GetY();

            corners[i][0] =  2.0f * rx / sw - 1.0f;
            corners[i][1] =  1.0f - 2.0f * ry / sh;
        }

        static float vertices[4 * 5];
        int idx = 0;

        // 左上
        vertices[idx++] = corners[0][0];
        vertices[idx++] = corners[0][1];
        vertices[idx++] = 0.0f;
        vertices[idx++] = 0.0f;
        vertices[idx++] = 1.0f;

        // 右上
        vertices[idx++] = corners[1][0];
        vertices[idx++] = corners[1][1];
        vertices[idx++] = 0.0f;
        vertices[idx++] = 1.0f;
        vertices[idx++] = 1.0f;

        // 右下
        vertices[idx++] = corners[2][0];
        vertices[idx++] = corners[2][1];
        vertices[idx++] = 0.0f;
        vertices[idx++] = 1.0f;
        vertices[idx++] = 0.0f;

        // 左下
        vertices[idx++] = corners[3][0];
        vertices[idx++] = corners[3][1];
        vertices[idx++] = 0.0f;
        vertices[idx++] = 0.0f;
        vertices[idx++] = 0.0f;

        return vertices;
    }

    void Sprite::Update()
    {
        if (m_luaRef.valid())
        {
            sol::table self_table = (sol::table)m_luaRef;
            if (self_table.valid())
            {
                sol::object update_obj = self_table["on_update"]; 
                if (update_obj.valid() && update_obj.is<sol::function>())
                {
                    sol::function update_func = update_obj.as<sol::function>();
                    update_func(self_table, Application::Get()->deltaTime);
                    return; 
                }
            }
        }

        
        // 执行 C++ 内部的Update逻辑
        if (m_Callback != nullptr)
        {
            m_Callback();
        }
    }

    std::shared_ptr<Sprite> Sprite::Clone()
    {
        std::shared_ptr<Sprite> c = std::make_shared<Sprite>(m_OriginalPicSrc);
        c->m_Texture = m_Texture;
        c->m_Scale = m_Scale;
        c->m_Angle = m_Angle;
        c->m_Pos = m_Pos;
        c->m_CurTexture = m_CurTexture;
        c->m_Collidable = m_Collidable;
        c->m_Visble = m_Visble;
        c->m_TextureCount = m_TextureCount;
        c->m_TextureIndex = m_TextureIndex;
        c->m_Callback = m_Callback;
        c->m_OnClick = m_OnClick;
        c->m_OnCollision = m_OnCollision;
        c->m_OnCreatedFn = m_OnCreatedFn;
        c->InOnCreated();
        return c;
    }

    float* Sprite::GenerateRotateMatrix() const
    {
        float mat[2][2];
        mat[0][0] = cos(m_Angle);
        mat[0][1] = -sin(m_Angle);
        mat[1][0] = sin(m_Angle);
        mat[1][1] = cos(m_Angle);
        return mat[0];
    }
}
