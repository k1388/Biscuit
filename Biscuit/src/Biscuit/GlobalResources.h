#pragma once
#include "BCUI/Font.h"
#include "Render/Texture.h"

namespace Biscuit
{
    inline std::vector<std::shared_ptr<BCUI::Font>> UIFonts;
    inline std::shared_ptr<BCUI::Font> GetFont(const std::string& name)
    {
        auto it = std::find_if(
            UIFonts.begin(), UIFonts.end(),
            [&name](const std::shared_ptr<BCUI::Font>& font) 
            {
                return font && font->GetFontName() == name;  
            });

        return (it != UIFonts.end()) ? *it : nullptr;
    }

    inline std::vector<std::shared_ptr<Texture>> Textures;
    inline std::shared_ptr<Texture> GetTexture(const std::string& name)
    {
        auto it = std::find_if(
        Textures.begin(), Textures.end(),
        [&name](const std::shared_ptr<Texture>& texture)   
        {
            return texture && texture->name == name;   
        });

        return (it != Textures.end()) ? *it : nullptr;
    }
}
