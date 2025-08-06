#pragma once
#include "Vec2.h"
#include "Vec3.h"


namespace Biscuit
{

    /// <summary>
    /// 四维向量
    /// </summary>
    class Vec4
    {
    public:
        Vec4(float x = 0, float y = 0, float z = 0, float w = 0):m_X(x), m_Y(y), m_Z(z), m_W(w) {}
        
        inline Vec4 Add(const Vec4& other = Vec4()) const
        {return Vec4(m_X + other.m_X, m_Y + other.m_Y , m_Z + other.m_Z, m_W + other.m_W);}
        
        inline Vec4 Sub(const Vec4& other = Vec4()) const
        {return Vec4(m_X - other.m_X, m_Y - other.m_Y , m_Z - other.m_Z, m_W - other.m_W);}
        
        inline float Dot(const Vec4& other = Vec4()) const
        {return m_X * other.m_X + m_Y * other.m_Y + m_Z * other.m_Z + m_W * other.m_W;}
        
        inline static Vec4 StaticAdd(const Vec4& a = Vec4(), const Vec4& b = Vec4())
        {return Vec4(a.m_X + b.m_X, a.m_Y + b.m_Y , a.m_Z + b.m_Z, a.m_W + b.m_W);}
        
        inline static Vec4 StaticSub(const Vec4& a = Vec4(), const Vec4& b = Vec4())
        {return Vec4(a.m_X - b.m_X, a.m_Y - b.m_Y , a.m_Z - b.m_Z, a.m_W - b.m_W);}
        
        inline static float StaticDot(const Vec4& a = Vec4(), const Vec4& b = Vec4())
        {return a.m_X * b.m_X + a.m_Y * b.m_Y + a.m_Z * b.m_Z + a.m_W * b.m_W;}
        
        Vec4 operator+(const Vec4& other) const
        {return Vec4(m_X + other.m_X, m_Y + other.m_Y , m_Z + other.m_Z, m_W + other.m_W);}
        
        Vec4 operator-(const Vec4& other) const
        {return Vec4(m_X - other.m_X, m_Y - other.m_Y , m_Z - other.m_Z, m_W - other.m_W);}
        
        Vec4 operator*(float num) const
        {return Vec4(m_X * num, m_Y * num, m_Z * num, m_W * num);}
        
        inline float Norm() const
        {return sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z + m_W * m_W);}

        inline void SetX(float x)
        {m_X = x;}
        
        inline void SetY(double y)
        {m_Y = y;}
        
        inline void SetZ(double z)
        {m_Z = z;}

        inline void SetW(double w)
        {m_W = w;}
        
        inline float GetX() const
        {return m_X;}
        
        inline float GetY() const
        {return m_Y;}
        
        inline float GetZ() const
        {return m_Z;}

        inline float GetW() const
        {return m_W;}

        inline float X() const
        {return m_X;}

        inline float Y() const
        {return m_Y;}

        inline float Z() const
        {return m_Z;}

        inline float W() const
        {return m_W;}
        
        inline void Set(float x, float y, float z, float w)
        {m_X = x;m_Y = y;m_Z = z;m_W = w;}

        inline const char* ToString() const
        {
            std::stringstream ss;
            ss << "(" << m_X << ", " << m_Y << ", " << m_Z << "," << m_W << ")";
            return ss.str().c_str();
        }
        
        inline Vec4(Vec2 convert)
        {
            m_X = convert.GetX();
            m_Y = convert.GetY();
            m_Z = 0;
            m_W = 0;
        }

        inline Vec4(Vec3 convert)
        {
            m_X = convert.GetX();
            m_Y = convert.GetY();
            m_Z = convert.GetZ();
            m_W = 0;
        }
        
    private:
        float m_X;
        float m_Y;
        float m_Z;
        float m_W;
    };
    inline Vec2::Vec2(const Vec4& convert)
    {
        m_X = convert.GetX();
        m_Y = convert.GetY();
    }
    inline Vec3::Vec3(const Vec4& convert)
    {
        m_X = convert.GetX();
        m_Y = convert.GetY();
        m_Z = convert.GetZ();
    }
}
