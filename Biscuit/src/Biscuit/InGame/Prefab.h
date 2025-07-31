#pragma once
#include "Sprite.h"

namespace Biscuit
{
    class Prefab
    {
    public:
        std::shared_ptr<Sprite> Instantiate() const;
        void LoadSprite(std::shared_ptr<Sprite> sprite);
        
    private:
        std::shared_ptr<Sprite> m_Sprite = nullptr;
    };
}
