#pragma once
#include "BCUI/Font.h"

namespace Biscuit
{
    inline std::vector<std::shared_ptr<BCUI::Font>> UIFonts;
    inline std::shared_ptr<BCUI::Font> GetFont(const std::string& name)
    {
        auto it = std::find_if(
            UIFonts.begin(), UIFonts.end(),
            [&name](const std::shared_ptr<BCUI::Font>& font)   // 加 const
            {
                return font && font->GetFontName() == name;   // 判空
            });

        return (it != UIFonts.end()) ? *it : nullptr;
    }
}
