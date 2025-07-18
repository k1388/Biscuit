#pragma once

namespace Biscuit
{
    class BISCUIT_API Vec3
    {
    public:
        Vec3(float x = 0, float y = 0, float z = 0):m_X(x), m_Y(y), m_Z(z) {}
        
        inline Vec3 Add(const Vec3& other = Vec3()) const
        {return Vec3(m_X + other.m_X, m_Y + other.m_Y , m_Z + other.m_Z);}
        inline Vec3 Sub(const Vec3& other = Vec3()) const
        {return Vec3(m_X - other.m_X, m_Y - other.m_Y , m_Z - other.m_Z);}
        inline float Dot(const Vec3& other = Vec3()) const
        {return m_X * other.m_X + m_Y * other.m_Y + m_Z * other.m_Z;}
        
        inline static Vec3 Add(const Vec3& a = Vec3(), const Vec3& b = Vec3())
        {return Vec3(a.m_X + b.m_X, a.m_Y + b.m_Y , a.m_Z + b.m_Z);}
        inline static Vec3 Sub(const Vec3& a = Vec3(), const Vec3& b = Vec3())
        {return Vec3(a.m_X - b.m_X, a.m_Y - b.m_Y , a.m_Z - b.m_Z);}
        inline static float Dot(const Vec3& a = Vec3(), const Vec3& b = Vec3())
        {return a.m_X * b.m_X + a.m_Y * b.m_Y + a.m_Z * b.m_Z;}
        Vec3 operator+(const Vec3& other) const
        {return Vec3(m_X + other.m_X, m_Y + other.m_Y , m_Z + other.m_Z);}
        Vec3 operator-(const Vec3& other) const
        {return Vec3(m_X - other.m_X, m_Y - other.m_Y , m_Z - other.m_Z);}

        inline float Norm() const
        {return sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z);}

        inline void SetX(float x)
        {m_X = x;}
        inline void SetY(double y)
        {m_Y = y;}
        inline void SetZ(double z)
        {m_Z = z;}
        inline float GetX() const
        {return m_X;}
        inline float GetY() const
        {return m_Y;}
        inline float GetZ() const
        {return m_Z;}
        inline void Set(float x, float y, float z)
        {m_X = x;m_Y = y;m_Z = z;}

        inline const char* ToString() const
        {
            std::stringstream ss;
            ss << "(" << m_X << ", " << m_Y << ", " << m_Z << ")";
            return ss.str().c_str();
        }
        inline Vec3(Vec2 convert)
        {
            m_X = convert.GetX();
            m_Y = convert.GetY();
            m_Z = 0;
        }
    private:
        float m_X;
        float m_Y;
        float m_Z;
    };

}
