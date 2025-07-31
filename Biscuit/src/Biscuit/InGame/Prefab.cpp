#include "pch.h"
#include "Prefab.h"

namespace Biscuit
{
    std::shared_ptr<Sprite> Prefab::Instantiate() const
    {
        if (m_Sprite != nullptr)
        {
            return m_Sprite->Clone();
        }
        return nullptr;
    }

    void Prefab::LoadSprite(std::shared_ptr<Sprite> sprite)
    {
        m_Sprite = sprite;
    }
}
