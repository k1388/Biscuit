#pragma once
#include "Biscuit/Render/Drawable.h"

namespace Biscuit
{
    class Sprite :public Drawable
    {
    public:
        using CallbackFn = std::function<void()>;
        using CollideCallbackFn = std::function<void(std::shared_ptr<Sprite>)>;
        using ClickCallbackFn = std::function<void(Vec2)>;
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

        virtual void Update()
        {
            if (m_Callback != nullptr)
            {
                m_Callback();
            }
           
        }

        void OnCollision(const CollideCallbackFn& fn)
        {
            m_OnCollision = fn;
        }
        
        virtual void InOnCollision(std::shared_ptr<Sprite> other)
        {
            if (m_OnCollision != nullptr)
            {
                m_OnCollision(other);
            }
        }

        inline void SetCollidable(bool Collidable)
        {
            m_Collidable = Collidable;
        }

        inline bool GetCollidable() const
        {
            return m_Collidable;
        }

        inline void OnClick(ClickCallbackFn fn)
        {
            m_OnClick = fn;
        }

        virtual void InOnClick(Vec2 pos)
        {
            if (m_OnClick != nullptr)
            {
                m_OnClick(pos);
            }
        }
    private:
        const float PI = 3.1415926f;
        float m_Angle = 0.0f;
        float* GenerateRotateMatrix() const;
        CallbackFn m_Callback = nullptr;
        CollideCallbackFn m_OnCollision = nullptr;
        bool m_Collidable = false;
        ClickCallbackFn m_OnClick = nullptr;
    };

}
