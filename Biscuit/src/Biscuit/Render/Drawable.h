#pragma once
#include "Position.h"
#include "Shader.h"
#include "Texture.h"

namespace Biscuit
{
    class Drawable
    {
    public:
        virtual ~Drawable(){}
        /// <summary>
        /// 可以渲染图片材质并进行简单变换的类
        /// </summary>
        /// <param name="picSrc">图片材质路径</param>
        Drawable(const std::string& picSrc);

        /// <summary>
        /// 绘制该对象
        /// </summary>
        void Draw();

        void Init();
        
        /// <summary>
        /// 获得对象名称
        /// </summary>
        /// <returns>对象名称</returns>
        inline std::string GetName() const
        {
            return m_Name;
        }

        /// <summary>
        /// 设置位置坐标
        /// </summary>
        /// <param name="position">坐标Vec2/Vec3</param>
        inline void SetPos(Vec3 position)
        {
            m_Pos = position;
            m_VertexChanged = true;
        }

        /// <summary>
        /// 设置位置坐标
        /// </summary>
        /// <param name="x">X</param>
        /// <param name="y">Y</param>
        inline void SetPos(float x, float y)
        {
            m_Pos = Vec3(x, y);
            m_VertexChanged = true;
        }

        /// <summary>
        /// 获得位置坐标
        /// </summary>
        /// <returns>位置坐标</returns>
        inline Position GetPos() const
        {
            return m_Pos;
        }

        /// <summary>
        /// 设置可视性（是否渲染）
        /// </summary>
        /// <param name="visible">可视性</param>
        inline void SetVisible(bool visible)
        {
            m_Visble = visible;
        }

        /// <summary>
        /// 获得可视性（是否渲染）
        /// </summary>
        /// <returns>可视性</returns>
        inline bool GetVisible() const
        {
            return m_Visble;
        }

        // inline void SetRotation(int angle)
        // {
        //     m_Angle = angle;
        // }
        //
        // inline void SetScale(float scale)
        // {
        //     m_Scale = scale;
        // }
        inline void SetScale(float scale) 
        {
            m_Scale = scale;
            m_VertexChanged = true;
        }
        
        inline float GetScale() const
        {
            return m_Scale;
        }
    protected:
        /// <summary>
        /// 将屏幕坐标变换为NDC
        /// </summary>
        /// <returns>顶点NDC数组</returns>
        virtual float* CoordTransform();
        bool m_Visble = true;
        int m_Pic_Width;
        int m_Pic_Height;
        Position m_Pos;
        int m_Pic_NrChannels;
        unsigned int m_Texture;
        float m_Vertices[4 * 5];
        float m_Scale = 1.0f;
        std::string m_Name;
        bool m_VertexChanged = true;
        std::vector<Texture*> m_Textures;
        Texture* m_CurTexture;
    private: 
        const unsigned int m_Indices[6] = {  
            0, 1, 3,  
            1, 2, 3   
        };
        unsigned int m_ShaderProgram;
        unsigned int m_VAO;
        unsigned int m_VBO;
        unsigned int m_EBO;
        std::unique_ptr<Shader> m_Shader; // 管理着色器生命周期
        
        /// <summary>
        /// 加载顶点，着色器，初始化VBO，EBO
        /// </summary>
        void Load();

        std::string m_t_PicSrc;
        
    };
}
