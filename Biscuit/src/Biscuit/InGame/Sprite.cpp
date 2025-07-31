#include "pch.h"
#include "Sprite.h"

#include "Biscuit/Application.h"

namespace Biscuit
{
    Sprite::Sprite(const std::string& picSrc) : Drawable(picSrc)
    {
        const float sw = float(Application::Get()->GetApplicationWindow().GetWidth());
        const float sh = float(Application::Get()->GetApplicationWindow().GetHeight());

        m_Pos = Vec2(sw/2,sh/2);
        m_OriginalPicSrc = picSrc;
        //Application::Get()->GetSpriteLayer()->AddSprite(this);
    }

    float* Sprite::CoordTransform()
    {
        const float sw = float(Application::Get()->GetApplicationWindow().GetWidth());
        const float sh = float(Application::Get()->GetApplicationWindow().GetHeight());

        const float w = m_CurTexture->picWidth  * m_Scale * 0.5f;
        const float h = m_CurTexture->picHeight * m_Scale * 0.5f;

        // 顺序：左上、右上、右下、左下
        float corners[4][2] = {
            { -w,  h },   
            {  w,  h }, 
            {  w, -h }, 
            { -w, -h }  
        };

        const float* m = GenerateRotateMatrix(); 
        const float  c = m[0], s = m[1];

        for (int i = 0; i < 4; ++i)
        {
            float x = corners[i][0];
            float y = corners[i][1];

            float rx = c * x - s * y;
            float ry = s * x + c * y;

            rx += m_Pos.GetX();
            ry += m_Pos.GetY();

            corners[i][0] =  2.0f * rx / sw - 1.0f;
            corners[i][1] =  1.0f - 2.0f * ry / sh;
        }

        static float vertices[4 * 5];
        int idx = 0;

        // 左上
        vertices[idx++] = corners[0][0];
        vertices[idx++] = corners[0][1];
        vertices[idx++] = 0.0f;
        vertices[idx++] = 0.0f;
        vertices[idx++] = 1.0f;

        // 右上
        vertices[idx++] = corners[1][0];
        vertices[idx++] = corners[1][1];
        vertices[idx++] = 0.0f;
        vertices[idx++] = 1.0f;
        vertices[idx++] = 1.0f;

        // 右下
        vertices[idx++] = corners[2][0];
        vertices[idx++] = corners[2][1];
        vertices[idx++] = 0.0f;
        vertices[idx++] = 1.0f;
        vertices[idx++] = 0.0f;

        // 左下
        vertices[idx++] = corners[3][0];
        vertices[idx++] = corners[3][1];
        vertices[idx++] = 0.0f;
        vertices[idx++] = 0.0f;
        vertices[idx++] = 0.0f;

        return vertices;
    }

    std::shared_ptr<Sprite> Sprite::Clone()
    {
        std::shared_ptr<Sprite> c = std::make_shared<Sprite>(m_OriginalPicSrc);
        c->m_Texture = m_Texture;
        c->m_Scale = m_Scale;
        c->m_Angle = m_Angle;
        c->m_Pos = m_Pos;
        c->m_CurTexture = m_CurTexture;
        c->m_Collidable = m_Collidable;
        c->m_Visble = m_Visble;
        c->m_TextureCount = m_TextureCount;
        c->m_TextureIndex = m_TextureIndex;
        c->m_Callback = m_Callback;
        c->m_OnClick = m_OnClick;
        c->m_OnCollision = m_OnCollision;
        c->m_OnCreatedFn = m_OnCreatedFn;
        return c;
    }

    float* Sprite::GenerateRotateMatrix() const
    {
        float mat[2][2];
        mat[0][0] = cos(m_Angle);
        mat[0][1] = -sin(m_Angle);
        mat[1][0] = sin(m_Angle);
        mat[1][1] = cos(m_Angle);
        return mat[0];
    }
}
