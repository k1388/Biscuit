#pragma once

#include "Shader.h"
#include "Texture.h"
#include "Biscuit/Math/Vec3.h"

namespace Biscuit
{
    class Drawable
    {
    public:
        
        
        Drawable(const Drawable&) = delete;
        Drawable& operator=(const Drawable&) = delete;
        
        virtual ~Drawable(){}
        
        /// <summary>
        /// 可以渲染图片材质并进行简单变换的类 (已弃用)
        /// </summary>
        /// <param name="picSrc">图片材质路径</param>
        Drawable(const std::string& picSrc);

        Drawable(const std::shared_ptr<Texture>& texture);

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
        /// 设置对象名称
        /// </summary>
        /// <param name="name">名称</param>
        inline void SetName(const std::string& name)
        {
            m_Name = name;
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
        inline Vec3 GetPos() const
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

        /// <summary>
        /// 设置缩放
        /// </summary>
        /// <param name="scale">缩放系数</param>
        inline void SetScale(float scale) 
        {
            m_Scale = scale;
            m_VertexChanged = true;
        }
        
        /// <summary>
        /// 获得缩放系数
        /// </summary>
        /// <returns>缩放系数</returns>
        inline float GetScale() const
        {
            return m_Scale;
        }

        /// <summary>
        /// 获得实际显示的像素宽度
        /// </summary>
        /// <returns>宽度</returns>
        inline float GetWidth() const
        {
            return m_CurTexture->picWidth * m_Scale;
        }

        /// <summary>
        /// 获得实际显示的像素高度
        /// </summary>
        /// <returns>高度</returns>
        inline float GetHeight() const
        {
            return m_CurTexture->picHeight * m_Scale;
        }

        /// <summary>
        /// 获得实际显示的像素大小
        /// </summary>
        /// <returns>大小</returns>
        inline Vec2 GetActualSize() const
        {
            return Vec2
            (
                m_CurTexture->picWidth * m_Scale,
                m_CurTexture->picHeight * m_Scale
            );
        }

        /// <summary>
        /// 获得材质数
        /// </summary>
        /// <returns>材质数</returns>
        inline int GetTextureCount() const
        {
            return m_TextureCount;
        }
        
        /// <summary>
        /// 新增材质
        /// </summary>
        /// <param name="picSrc">图片路径</param>
        /// <returns>是否成功</returns>
        bool AddTexture(const std::string& picSrc);

        /// <summary>
        /// 设置当前材质
        /// </summary>
        /// <param name="index">材质编号</param>
        void SetTexture(unsigned int index);

        /// <summary>
        /// 切换到下一个材质
        /// </summary>
        void NextTexture();

    protected:
        bool                                    m_Visble = true;
        int                                     m_Pic_Width;
        int                                     m_Pic_Height;
        Vec3                                    m_Pos;
        int                                     m_Pic_NrChannels;
        unsigned int                            m_Texture;
        float                                   m_Vertices[4 * 5];
        float                                   m_Scale = 1.0f;
        std::string                             m_Name;
        bool                                    m_VertexChanged = true;
        std::vector<std::shared_ptr<Texture>>   m_Textures;
        std::shared_ptr<Texture>                m_CurTexture;
        int                                     m_TextureCount = 0;
        int                                     m_TextureIndex = 0;

        /// <summary>
        /// 将屏幕坐标变换为NDC
        /// </summary>
        /// <returns>顶点NDC数组</returns>
        virtual float* CoordTransform();
        
    private: 
        const unsigned int m_Indices[6] = {  
            0, 1, 3,  
            1, 2, 3   
        };
        unsigned int            m_ShaderProgram;
        unsigned int            m_VAO;
        unsigned int            m_VBO;
        unsigned int            m_EBO;
        std::unique_ptr<Shader> m_Shader; // 管理着色器生命周期
        bool                    m_HasInitialized = false;
        std::string             m_t_PicSrc;
        
        /// <summary>
        /// 加载顶点，着色器，初始化VBO，EBO
        /// </summary>
        void Load();
        
    };
}
