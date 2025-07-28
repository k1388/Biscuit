#pragma once
#include "Layer.h"
#include "InGame/Sprite.h"

namespace Biscuit
{
    class SpriteLayer : public Layer
    {
    public:
        void AddSprite(std::shared_ptr<Sprite> gameObject);
        void OnUpdate() override;
        void InitAllSprites();
        void CheckAllCollisions();
        void CheckMouseCollisions(Vec2 pos);
    private:
        std::vector<std::shared_ptr<Sprite>> m_Sprites;
    };
}
