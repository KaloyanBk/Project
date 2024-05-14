#pragma once

#include <unordered_map>
#include <string>

enum Fonts
{
    DOSIS_LIGHT = 0,
};
const std::unordered_map<Fonts, std::string> resourcePathsFonts = {

    {DOSIS_LIGHT, "Fonts/Dosis-Light.ttf"},

};