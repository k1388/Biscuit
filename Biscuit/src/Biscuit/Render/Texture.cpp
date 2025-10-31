#include "pch.h"
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Biscuit
{
    Texture::Texture(const std::string& filePath, const std::string& textureName)
    {
        name = textureName;

        // 强制加载为 4 通道（RGBA）
        //stbi_set_flip_vertically_on_load(true);
        unsigned char* t_Pic_Data = stbi_load(
            filePath.c_str(),
            &picWidth,
            &picHeight,
            &picChannels,
            4 // 强制加载为 RGBA
        );

        if (!t_Pic_Data)
        {
            // 加载失败处理
            std::cerr << "Failed to load texture: " << filePath << std::endl;
            return;
        }

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA, // 内部格式
            picWidth,
            picHeight,
            0,
            GL_RGBA, // 数据格式
            GL_UNSIGNED_BYTE,
            t_Pic_Data
        );

        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(t_Pic_Data);
    }
}