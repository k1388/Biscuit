#pragma once
#include "Biscuit/Render/Drawable.h"

namespace Biscuit
{
    class Prefab;
    class Sprite :public Drawable
    {
    public:
        
        using CallbackFn = std::function<void()>;

        using CollideCallbackFn = std::function<void(std::shared_ptr<Sprite>)>;

        using ClickCallbackFn = std::function<void(Vec2)>;

        Sprite(const std::string& picSrc);
        float* CoordTransform() override;

        /// <summary>
        /// 设置旋转角度
        /// </summary>
        /// <param name="angle">角度（角度制）</param>
        inline void SetRotation(float angle)
        {
            m_Angle = angle / 180.0f * PI;
            m_VertexChanged = true;
        }

        /// <summary>
        /// 逆时针旋转
        /// </summary>
        /// <param name="angle">角度（角度制）</param>
        inline void Rotate(float angle)
        {
            m_Angle += angle / 180.0f * PI;
            m_VertexChanged = true;
        }

        /// <summary>
        /// 获得当前旋转角度
        /// </summary>
        /// <returns>角度（角度制）</returns>
        inline float GetRotation() const
        {
            return m_Angle;
        }

        /// <summary>
        /// 设置每帧Sprite的行为
        /// </summary>
        /// <param name="fn">回调函数</param>
        void OnUpdate(const CallbackFn& fn)
        {
            m_Callback = fn;
        }

        /// <summary>
        /// 每帧调用一次
        /// </summary>
        virtual void Update()
        {
            if (m_Callback != nullptr)
            {
                m_Callback();
            }
           
        }

        /// <summary>
        /// 设置受到碰撞的行为
        /// </summary>
        /// <param name="fn">回调函数</param>
        void OnCollision(const CollideCallbackFn& fn)
        {
            m_OnCollision = fn;
        }
        
        /// <summary>
        /// 受到碰撞调用
        /// </summary>
        /// <param name="other">与Sprite碰撞的对象</param>
        virtual void InOnCollision(std::shared_ptr<Sprite> other)
        {
            if (m_OnCollision != nullptr)
            {
                m_OnCollision(other);
            }
        }

        /// <summary>
        /// 设置是否参与碰撞
        /// </summary>
        /// <param name="Collidable">是否参与碰撞</param>
        inline void SetCollidable(bool Collidable)
        {
            m_Collidable = Collidable;
        }

        /// <summary>
        /// 获得是否参与碰撞
        /// </summary>
        /// <returns>是否参与碰撞</returns>
        inline bool GetCollidable() const
        {
            return m_Collidable;
        }

        /// <summary>
        /// 鼠标点击后的行为
        /// </summary>
        /// <param name="fn">回调函数</param>
        inline void OnClick(ClickCallbackFn fn)
        {
            m_OnClick = fn;
        }

        /// <summary>
        /// 鼠标点击后调用
        /// </summary>
        /// <param name="pos">鼠标位置</param>
        virtual void InOnClick(Vec2 pos)
        {
            if (m_OnClick != nullptr)
            {
                m_OnClick(pos);
            }
        }

        void OnCreated(CallbackFn fn)
        {
            m_Callback = fn;
        }

        virtual void InOnCreated()
        {
            if (m_OnCreatedFn != nullptr)
            {
                m_OnCreatedFn();
            }
        }
    
    protected:
        friend class Prefab;
        virtual std::shared_ptr<Sprite> Clone();
        
    private:
        const float PI = 3.1415926f;
        float m_Angle = 0.0f;
        float* GenerateRotateMatrix() const;
        CallbackFn m_Callback = nullptr;
        CollideCallbackFn m_OnCollision = nullptr;
        bool m_Collidable = false;
        ClickCallbackFn m_OnClick = nullptr;
        CallbackFn m_OnCreatedFn = nullptr;
        std::string m_OriginalPicSrc = "";
    };

}
