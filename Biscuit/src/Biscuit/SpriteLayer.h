#pragma once
#include "Layer.h"
#include "InGame/Sprite.h"

namespace Biscuit
{
    /// <summary>
    /// 渲染游戏对象的层
    /// </summary>
    class SpriteLayer : public Layer
    {
    public:
        /// <summary>
        /// 新增一个Sprite到场景
        /// </summary>
        /// <param name="gameObject">Sprite指针</param>
        void AddSprite(std::shared_ptr<Sprite> gameObject);

        /// <summary>
        /// SpriteLayer每帧更新方法
        /// </summary>
        void OnUpdate() override;

        /// <summary>
        /// 调用所有Sprite的初始化方法
        /// </summary>
        void InitAllSprites();

        /// <summary>
        /// 检测所有Sprite碰撞
        /// </summary>
        void CheckAllCollisions();

        /// <summary>
        /// 检测所有Sprite鼠标点击
        /// </summary>
        /// <param name="pos">鼠标指针位置</param>
        void CheckMouseCollisions(Vec2 pos);

        void RemoveSprite(std::shared_ptr<Sprite> gameObject);
        
    private:
        std::vector<std::shared_ptr<Sprite>> m_Sprites;
    };
}
