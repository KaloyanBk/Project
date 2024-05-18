#pragma once

#include <unordered_map>
#include <string>

enum Fonts
{
    DOSIS_LIGHT = 0,
    GAME_OVER,
    FONTS_COUNT
};
const std::unordered_map<Fonts, std::string> resourcePathsFonts = {

    {DOSIS_LIGHT, "Fonts/Dosis-Light.ttf"},
    {GAME_OVER, "Fonts/GAME_glm.ttf"},


};