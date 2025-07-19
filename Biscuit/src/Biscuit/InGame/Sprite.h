#pragma once
#include "Biscuit/Render/Drawable.h"

namespace Biscuit
{
    class Sprite :public Drawable
    {
    public:
        using CallbackFn = std::function<void()>;
        Sprite(const std::string& picSrc);
        float* CoordTransform() override;
        inline void SetRotation(float angle)
        {
            m_Angle = angle / 180.0f * PI;
            m_VertexChanged = true;
        }
        inline void Rotate(float angle)
        {
            m_Angle += angle / 180.0f * PI;
            m_VertexChanged = true;
        }
        inline float GetRotation() const
        {
            return m_Angle;
        }

        void OnUpdate(const CallbackFn& fn)
        {
            m_Callback = fn;
        }

        void Update()
        {
            if (m_Callback != nullptr)
            {
                m_Callback();
            }
           
        }
    private:
        const float PI = 3.1415926f;
        float m_Angle = 0.0f;
        float* GenerateRotateMatrix() const;
        CallbackFn m_Callback = nullptr;
    };

}
