#pragma once

#include <unordered_map>
#include <string>

enum Textures
{
    // Player
    PLAYER = 0,

    // Side Guns
    SIDE_GUN_UP,
    SIDE_GUN_DOWN,

    // Enemy
    ENEMY,

    // Total
    NUM_RESOURCES // Renamed from NUM_TEXTURES for clarity
};

const std::unordered_map<Textures, std::string> resourcePaths = {
    // Player
    {PLAYER, "Sprites/Ship.png"},

    // Side Guns
    {SIDE_GUN_UP, "Sprites/SideGuns/Upper/peaShooterTier1.png"},
    {SIDE_GUN_DOWN, "Sprites/SideGuns/Lower/peaShooterTier1.png"},

    // Enemy
    {ENEMY, "Sprites/Enemys/Enemy.png"},
};

