#include "pch.h"
#include "SpriteLayer.h"

namespace Biscuit
{
    void Biscuit::SpriteLayer::AddSprite(Sprite* sprite)
    {
        m_Sprites.push_back(sprite);
        sprite->Init();
    }

    void SpriteLayer::OnUpdate()
    {
        for (auto& sprite : m_Sprites)
        {
            sprite->Update();
            sprite->Draw();
        }
    }

    void SpriteLayer::InitAllSprites()
    {
        for (auto& sprite : m_Sprites)
        {
            sprite->Init();
        }
    }
    
}
