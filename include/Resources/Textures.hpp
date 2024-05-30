/**
 * @file Textures.hpp
 * @author Kaloyen
 * @brief This is the header file for the Textures enum, which is used to store the paths to the textures used in the game.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <unordered_map>
#include <string>

enum Textures
{
    // Player
    PLAYER = 0,

    // Enemy
    ENEMY_MOVE_LEFT,
    ENEMY_FOLLOW,

    // Total
    NUM_RESOURCES // Renamed from NUM_TEXTURES for clarity
};
enum SideGuns
{
    // Player
    PEA_SHOOTER = 0,

    // Total
    NUM_SIDE_GUNS
};

enum Levels
{
    // Bullets
    SIDE_GUN_LEVEL1 = 0,

    SIDE_GUN_LEVEL2,
    SIDE_GUN_LEVEL3,

    // Total
    NUM_SIDE_GUN_LEVELS
};

const std::unordered_map<Textures, std::string> resourcePaths = {
    // Player
    {PLAYER, "include/Resources/Sprites/Ship.png"},

    // Enemy
    {ENEMY_MOVE_LEFT, "include/Resources/Sprites/Enemys/MoveLeft.png"},
    {ENEMY_FOLLOW, "include/Resources/Sprites/Enemys/Follow.png"},
};

const std::unordered_map<Levels, std::string> PeaShooterUp = {
    {SIDE_GUN_LEVEL1, "include/Resources/Sprites/SideGuns/Upper/peaShooterTier1.png"},
    {SIDE_GUN_LEVEL2, "include/Resources/Sprites/SideGuns/Upper/peaShooterTier2.png"},
    {SIDE_GUN_LEVEL3, "include/Resources/Sprites/SideGuns/Upper/peaShooterTier3.png"},
};

const std::unordered_map<Levels, std::string> PeaShooterDown = {
    {SIDE_GUN_LEVEL1, "include/Resources/Sprites/SideGuns/Lower/peaShooterTier1.png"},
    {SIDE_GUN_LEVEL2, "include/Resources/Sprites/SideGuns/Lower/peaShooterTier2.png"},
    {SIDE_GUN_LEVEL3, "include/Resources/Sprites/SideGuns/Lower/peaShooterTier3.png"},
};

const std::unordered_map<SideGuns, std::unordered_map<Levels, std::string>> SideGunsUp = {
    // Player
    {PEA_SHOOTER, PeaShooterUp},

};
const std::unordered_map<SideGuns, std::unordered_map<Levels, std::string>> SideGunsDown = {
    // Player
    {PEA_SHOOTER, PeaShooterDown},

};