#pragma once

namespace Biscuit
{
    class Texture
    {
    public:
        int             picWidth;
        int             picHeight;
        int             picChannels;
        unsigned int    textureID;
        std::string     name;
        
        Texture(int picWidth, int picHeight, int picChannels, unsigned int textureID):
        picHeight(picHeight),
        picWidth(picWidth),
        picChannels(picChannels),
        textureID(textureID)
        {}

        Texture(const std::string& filePath, const std::string& textureName);
        
    };
    
}
