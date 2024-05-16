#pragma once

#include <unordered_map>
#include <string>

// Enum for all bullet textures
enum BulletTypes
{
    // Bullets
    LASER_BULLET = 0,
    LIGHTNING_BULLET,
    DARK_MATTER_BULLET,
    NUCLIER_MATERIAL_BULLET,
    PLASMA_BULLET,
    PLANETARY_BOMB_BULLET,

    // Side Guns
    SIDE_GUN_PEA_SHOOTER_BULLET,

    // Total
    NUM_BULLETS // Renamed from NUM_TEXTURES for clarity
};

const std::unordered_map<BulletTypes, std::string> resourcePathsBullets = {
    // Player
    {LASER_BULLET, "Sprites/LaserBullets/Bullet.png"},
    {LIGHTNING_BULLET, "Sprites/LaserBullets/29.png"},
    {DARK_MATTER_BULLET, "Sprites/LaserBullets/47.png"},
    {NUCLIER_MATERIAL_BULLET, "Sprites/LaserBullets/65.png"},
    {PLASMA_BULLET, "Sprites/LaserBullets/48.png"},
    {PLANETARY_BOMB_BULLET, "Sprites/LaserBullets/55.png"},

    // Side Guns
    {SIDE_GUN_PEA_SHOOTER_BULLET, "Sprites/LaserBullets/01.png"},
};

// Enum for all bullet damage types

const std::unordered_map<BulletTypes, unsigned int> resourcePathsBulletsDamage = {
    // Player
    {LASER_BULLET, 1},
    {LIGHTNING_BULLET, 2},
    {DARK_MATTER_BULLET, 3},
    {NUCLIER_MATERIAL_BULLET, 4},
    {PLASMA_BULLET, 5},
    {PLANETARY_BOMB_BULLET, 6},

    // Side Guns
    {SIDE_GUN_PEA_SHOOTER_BULLET, 1},
};