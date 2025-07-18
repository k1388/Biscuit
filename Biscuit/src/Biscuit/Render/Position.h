#pragma once
#include "Biscuit/Application.h"
#include "Biscuit/Math/Vec2.h"
#include "Biscuit/Math/Vec3.h"

namespace Biscuit
{
    class Position
    {
    public:
        Position()
        {
            m_Pos = Vec3(
                Application::Get()->GetApplicationWindow().GetWidth()/2.0f,
                Application::Get()->GetApplicationWindow().GetHeight()/2.0f
            );
        }
        Position(const Vec3& position)
        {
            m_Pos = position;
        }
        Position(Vec2 position)
        {
            m_Pos = position;
        }
        Position(float x, float y)
        {
            m_Pos = Vec3(x, y);
        }
        Position(float x, float y, float z)
        {
            m_Pos = Vec3(x, y, z);
        }
        inline void SetPos(Vec2 position)
        {m_Pos = position;}
        inline void SetPos(float x, float y)
        {m_Pos = Vec2(x, y);}
        inline void SetPos(float x, float y, float z)
        {m_Pos = Vec3(x, y, z);}
        inline void SetPos(Vec3 position)
        {m_Pos = position;}
        
        inline Vec3 GetPos() const {return m_Pos;}
        inline float GetX() const {return m_Pos.GetX();}
        inline float GetY() const {return m_Pos.GetY();}
    private:
        Vec3 m_Pos;
    };        


}
