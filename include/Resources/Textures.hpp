#pragma once

#include <unordered_map>
#include <string>

enum Textures
{
    // Player
    PLAYER = 0,

    // Bullets
    LASER_BULLET,
    LIGHTNING_BULLET,
    DARK_MATTER_BULLET,
    NUCLIER_MATERIAL_BULLET,
    PLASMA_BULLET,
    PLANETARY_BOMB_BULLET,

    // Side Guns
    SIDE_GUN_UP,
    SIDE_GUN_DOWN,
    SIDE_GUN_BULLET,

    // Enemy
    ENEMY,

    // Total
    NUM_RESOURCES // Renamed from NUM_TEXTURES for clarity
};

const std::unordered_map<Textures, std::string> resourcePaths = {
    // Player
    {PLAYER, "Sprites/Ship.png"},

    // Bullets
    {LASER_BULLET, "Sprites/LaserBullets/Bullet.png"},
    {LIGHTNING_BULLET, "Sprites/LaserBullets/29.png"},
    {DARK_MATTER_BULLET, "Sprites/LaserBullets/47.png"},
    {NUCLIER_MATERIAL_BULLET, "Sprites/LaserBullets/65.png"},
    {PLASMA_BULLET, "Sprites/LaserBullets/48.png"},
    {PLANETARY_BOMB_BULLET, "Sprites/LaserBullets/55.png"},

    // Side Guns
    {SIDE_GUN_UP, "Sprites/SideGuns/Upper/peaShooterTier1.png"},
    {SIDE_GUN_DOWN, "Sprites/SideGuns/Lower/peaShooterTier1.png"},
    {SIDE_GUN_BULLET, "Sprites/LaserBullets/01.png"},

    // Enemy
    {ENEMY, "Sprites/Enemys/Enemy.png"},
};

