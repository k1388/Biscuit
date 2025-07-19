#pragma once
#include "Layer.h"
#include "InGame/Sprite.h"

namespace Biscuit
{
    class SpriteLayer : public Layer
    {
    public:
        void AddSprite(Sprite* gameObject);
        void OnUpdate() override;
        void InitAllSprites();
    private:
        std::vector<Sprite*> m_Sprites;
    };
}
