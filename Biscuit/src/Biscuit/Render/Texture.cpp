#include "pch.h"
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
namespace Biscuit
{
    Texture::Texture(const std::string& filePath, const std::string& textureName)
    {
        name = textureName;
        unsigned char* t_Pic_Data = stbi_load
        (
            filePath.c_str(),
            &picWidth,
            &picHeight,
            &picChannels,
            0
        );
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        if (t_Pic_Data)
        {
            glTexImage2D
            (
                GL_TEXTURE_2D,
                0,
                picChannels < 4?GL_RGB:GL_RGBA,
                picWidth,
                picHeight,
                0,
                picChannels < 4?GL_RGB:GL_RGBA,
                GL_UNSIGNED_BYTE,
                t_Pic_Data
            );
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        stbi_image_free(t_Pic_Data);
    }
}
