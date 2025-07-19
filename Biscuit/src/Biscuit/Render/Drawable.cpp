#include "pch.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Drawable.h"
#include "Shader.h"
#include "Biscuit/Application.h"
#include "Glad/glad.h"

namespace Biscuit
{
    Drawable::Drawable(const std::string& picSrc)
        :m_t_PicSrc(picSrc)
    {
        m_Pos = Position(100,100);
        m_Name = "null";
    }


    void Drawable::Draw()
    {
        if (!m_Visble)
        {
            return;
        }
        if (m_VertexChanged)
        {
            memcpy(m_Vertices, CoordTransform(), sizeof(m_Vertices));
            glBindVertexArray(m_VAO);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_DYNAMIC_DRAW);
            m_VertexChanged = false;
        }
        
        glUseProgram(m_Shader->GetShaderProgram());
        glUniform1i(glGetUniformLocation(m_ShaderProgram, "myTexture"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_Texture);
        glBindVertexArray(m_VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void Drawable::Init()
    {
        //stbi_set_flip_vertically_on_load(true);
        unsigned char* t_Pic_Data = stbi_load(
            m_t_PicSrc.c_str(),
            &m_Pic_Width,
            &m_Pic_Height,
            &m_Pic_NrChannels,
            0
        );
        glGenTextures(1, &m_Texture);
        glBindTexture(GL_TEXTURE_2D, m_Texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        if (t_Pic_Data)
        {
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                m_Pic_NrChannels < 4?GL_RGB:GL_RGBA,
                m_Pic_Width,
                m_Pic_Height,
                0,
                m_Pic_NrChannels < 4?GL_RGB:GL_RGBA,
                GL_UNSIGNED_BYTE,
                t_Pic_Data
            );
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        stbi_image_free(t_Pic_Data);
        Load();
        
    }


    float* Drawable::CoordTransform()
    {
                
        // float vertices[4 * 5] = {
        //     // ---- 位置 ---     - 纹理坐标 -
        //     0.5f,  0.5f, 0.0f,    1.0f, 1.0f,   // 右上
        //     0.5f, -0.5f, 0.0f,    1.0f, 0.0f,   // 右下
        //    -0.5f, -0.5f, 0.0f,    0.0f, 0.0f,   // 左下
        //    -0.5f,  0.5f, 0.0f,    0.0f, 1.0f    // 左上
        // };
        
        float sw = Application::Get()->GetApplicationWindow().GetWidth();
        float sh = Application::Get()->GetApplicationWindow().GetHeight();
        float rux, ruy, rdx, rdy, ldx, ldy, lux, luy;
        lux = (2.0f * m_Pos.GetX()) / sw - 1.0f;
        luy = 1.0f - (2.0f * m_Pos.GetY()) / sh;
        rux = lux + (m_Pic_Width / sw) * m_Scale;
        ruy =  luy;
        ldx = lux;
        ldy = luy - (m_Pic_Height / sh) * m_Scale;
        rdx = rux;
        rdy = ldy;

        // 缩放

        
        float vertices[4 * 5] = {
            // ---- 位置 ---    - 纹理坐标 -
            lux, luy, 0.0f,    1.0f, 1.0f,   // 左上
            rux, ruy, 0.0f,    1.0f, 0.0f,   // 右上
            rdx, rdy, 0.0f,    0.0f, 0.0f,   // 右下
            ldx, ldy, 0.0f,    0.0f, 1.0f    // 左下
        };

        return vertices;
    }


    void Drawable::Load()
    {
        memcpy(m_Vertices, CoordTransform(), sizeof(m_Vertices));
        

        const char* verSrc = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec2 aTexCoord;

            out vec2 TexCoord;

            void main()
            {
                gl_Position = vec4(aPos, 1.0);
                TexCoord = aTexCoord;
            }
        )";

        const char* fragSrc = R"(
            #version 330 core
            out vec4 color;

            in vec2 TexCoord;

            uniform sampler2D myTexture;

            void main()
            {
                color = texture(myTexture, TexCoord);
            }
        )";
        m_Shader = std::make_unique<Shader>(verSrc, fragSrc);

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_DYNAMIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indices), m_Indices, GL_DYNAMIC_DRAW);
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        glBindVertexArray(0); // 解绑
    }

    // float* Drawable::GenerateRotateMatrix() const
    // {
    //     float mat[2][2];
    //     mat[0][0] = cos(m_Angle);
    //     mat[0][1] = -sin(m_Angle);
    //     mat[1][0] = sin(m_Angle);
    //     mat[1][1] = cos(m_Angle);
    //     return mat[0];
    // }
}

