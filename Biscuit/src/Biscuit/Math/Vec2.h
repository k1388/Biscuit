#pragma once
namespace Biscuit
{
    class BISCUIT_API Vec2
    {
    public:
        Vec2(float x = 0, float y = 0):m_X(x), m_Y(y) {}
        
        inline Vec2 Add(const Vec2& other = Vec2()) const
        {return Vec2(m_X + other.m_X, m_Y + other.m_Y);}
        inline Vec2 Sub(const Vec2& other = Vec2()) const
        {return Vec2(m_X - other.m_X, m_Y - other.m_Y);}
        inline float Dot(const Vec2& other = Vec2()) const
        {return m_X * other.m_X + m_Y * other.m_Y;}
        
        inline static Vec2 Add(const Vec2& a = Vec2(), const Vec2& b = Vec2())
        {return Vec2(a.m_X + b.m_X, a.m_Y + b.m_Y);}
        inline static Vec2 Sub(const Vec2& a = Vec2(), const Vec2& b = Vec2())
        {return Vec2(a.m_X - b.m_X, a.m_Y - b.m_Y);}
        inline static float Dot(const Vec2& a = Vec2(), const Vec2& b = Vec2())
        {return a.m_X * b.m_X + a.m_Y * b.m_Y;}
        Vec2 operator+(const Vec2& other) const
        {return Vec2(m_X + other.m_X, m_Y + other.m_Y);}
        Vec2 operator-(const Vec2& other) const
        {return Vec2(m_X - other.m_X, m_Y - other.m_Y);}

        inline float Norm() const
        {return sqrt(m_X * m_X + m_Y * m_Y);}

        inline void SetX(float x)
        {m_X = x;}
        inline void SetY(double y)
        {m_Y = y;}
        inline float GetX() const
        {return m_X;}
        inline float GetY() const
        {return m_Y;}
        inline void Set(float x, float y)
        {m_X = x;m_Y = y;}

        inline const char* ToString() const
        {
            std::stringstream ss;
            ss << "(" << m_X << ", " << m_Y << ")";
            return ss.str().c_str();
        }

    private:
        float m_X;
        float m_Y;
        
    };

}
