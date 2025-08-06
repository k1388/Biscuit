#pragma once
#include "Sprite.h"

namespace Biscuit
{
    /// <summary>
    /// 预制体，用于Sprite的克隆，需要一个Sprite作为模板
    /// </summary>
    class Prefab
    {
    public:
        std::shared_ptr<Sprite> Instantiate() const;
        void LoadSprite(std::shared_ptr<Sprite> sprite);
        
    private:
        std::shared_ptr<Sprite> m_Sprite = nullptr;
    };
}
