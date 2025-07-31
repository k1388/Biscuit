#include "pch.h"
#include "SpriteLayer.h"

namespace Biscuit
{
    void SpriteLayer::AddSprite(std::shared_ptr<Sprite> sprite)
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

    void SpriteLayer::CheckAllCollisions()
    {
        unsigned int n = m_Sprites.size();
        if (n <= 1)
        {
            return;
        }
        for (int i = 0; i < n; ++i)
        {
            auto& sprite = m_Sprites[i];
            for (int j = i + 1; j < n; ++j)
            {
                auto& other = m_Sprites[j];
                // 判断是否可碰撞
                if (!sprite->GetCollidable())
                {
                    break;
                }
                if (!other->GetCollidable())
                {
                    continue;
                }

                Vec3 pos1 = sprite->GetPos();
                Vec3 pos2 = other->GetPos();
                Vec2 size1 = sprite->GetActualSize();
                Vec2 size2 = other->GetActualSize();
                if (!(sprite->GetRotation() && other->GetRotation()))   // 如果未旋转，用AABB检测
                {
                    if
                    (!(
                        pos1.X() + size1.X()/2 < pos2.X() - size2.X()/2 ||
                        pos1.X() - size1.X()/2 < pos2.X() + size2.X()/2 ||
                        pos1.Y() + size1.Y() < pos2.Y() - size2.Y()/2 ||
                        pos1.Y() - size1.Y() < pos2.Y() + size2.Y()/2)
                    )
                    {
                        sprite->InOnCollision(other);
                        other->InOnCollision(sprite);
                    }
                }
                else    // 如果旋转，用SAT检测
                {
                    const float con =  3.1415926f / 180.0f;

                    // ====== 构造 OBB 1 ======
                    float c1 = cosf(sprite->GetRotation() * con);
                    float s1 = sinf(sprite->GetRotation() * con);
                    Vec2 half1 = { sprite->GetWidth() * 0.5f, sprite->GetHeight() * 0.5f };
                    Vec2 ax1x = {  c1 * half1.X(),  s1 * half1.X() };
                    Vec2 ax1y = { -s1 * half1.Y(), c1 * half1.Y() };
                    Vec2 cen1 = { pos1.X(), pos1.Y() };

                    // ====== 构造 OBB 2 ======
                    float c2 = cosf(other->GetRotation() * con);
                    float s2 = sinf(other->GetRotation() * con);
                    Vec2 half2 = { other->GetWidth() * 0.5f, other->GetHeight() * 0.5f };
                    Vec2 ax2x = {  c2 * half2.X(),  s2 * half2.X() };
                    Vec2 ax2y = { -s2 * half2.Y(), c2 * half2.Y() };
                    Vec2 cen2 = { pos2.X(), pos2.Y() };

                    // 四条分离轴（各自的两条边方向）
                    Vec2 axes[4] =
                    {
                        Vec2(c1, s1),
                        Vec2(-s1, c1),
                        Vec2(c2, s2),
                        Vec2(-s2, c2)
                    };

                    bool overlap = true;
                    for (int k = 0; k < 4; ++k)
                    {
                        Vec2 axis = axes[k];
                        float d1[4] = {
                            (cen1 + ax1x + ax1y).Dot(axis),
                            (cen1 - ax1x + ax1y).Dot(axis),
                            (cen1 - ax1x - ax1y).Dot(axis),
                            (cen1 + ax1x - ax1y).Dot(axis)
                        };
                        float d2[4] = {
                            (cen2 + ax2x + ax2y).Dot(axis),
                            (cen2 - ax2x + ax2y).Dot(axis),
                            (cen2 - ax2x - ax2y).Dot(axis),
                            (cen2 + ax2x - ax2y).Dot(axis)
                        };
                        float min1 = std::min({d1[0], d1[1], d1[2], d1[3]});
                        float max1 = std::max({d1[0], d1[1], d1[2], d1[3]});
                        float min2 = std::min({d2[0], d2[1], d2[2], d2[3]});
                        float max2 = std::max({d2[0], d2[1], d2[2], d2[3]});
                        if (max1 < min2 || max2 < min1)
                        {
                            overlap = false;
                            break;
                        }
                    }
                    if (overlap)
                    {
                        sprite->InOnCollision(other);
                        other->InOnCollision(sprite);
                    }
                    
                }

            }
        }
    }

    void SpriteLayer::CheckMouseCollisions(Vec2 pos)
    {
        for (auto it = m_Sprites.rbegin(); it != m_Sprites.rend(); ++it)
        {
            Sprite* sp = it->get();

            Vec3  p  = sp->GetPos();
            Vec2  half = sp->GetActualSize() * 0.5f;
            
            if (std::abs(sp->GetRotation()) < 0.001f)
            {
                
                if (pos.X() >= p.X() - half.X() && pos.X() <= p.X() + half.X() &&
                    pos.Y() >= p.Y() - half.Y() && pos.Y() <= p.Y() + half.Y())
                {
                    sp->InOnClick(pos);       
                    return;                    
                }
            }
            else
            {
                const float con = 3.1415926f / 180.0f;
                float c = cosf(-sp->GetRotation() * con);
                float s = sinf(-sp->GetRotation() * con);

                Vec2 local = Vec2(
                    (pos.X() - p.X()) * c - (pos.Y() - p.Y()) * s,
                    (pos.X() - p.X()) * s + (pos.Y() - p.Y()) * c);

                if (std::abs(local.X()) <= half.X() && std::abs(local.Y()) <= half.Y())
                {
                    sp->InOnClick(pos);
                    return;
                }
            }
        }
    }

    void SpriteLayer::RemoveSprite(std::shared_ptr<Sprite> gameObject)
    {
        m_Sprites.erase(find(m_Sprites.begin(), m_Sprites.end(), gameObject));
    }
}
