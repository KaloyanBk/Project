/**
 * @file Fonts.hpp
 * @author Kaloyan
 * @brief This is the header file for the Fonts enum, which is used to store the paths to the fonts used in the game.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
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