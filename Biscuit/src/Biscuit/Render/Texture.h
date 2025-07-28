#pragma once
namespace Biscuit
{
    class Texture
    {
    public:
        int picWidth;
        int picHeight;
        int picChannels;
        unsigned int textureID;

        Texture(int picWidth, int picHeight, int picChannels, unsigned int textureID):
        picHeight(picHeight),
        picWidth(picWidth),
        picChannels(picChannels),
        textureID(textureID)
        {}
    };
    
}
