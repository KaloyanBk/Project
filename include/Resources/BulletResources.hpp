#pragma once

#include <unordered_map>
#include <string>

enum BulletLevels
{
    // Bullets
    LEVEL1 = 0,

    LEVEL2,
    LEVEL3,
    LEVEL4,
    LEVEL5,

    // Total
    NUM_BULLET_LEVELS
};

const std::unordered_map<BulletLevels, std::string> resourcePathsLaserBullets = {
    {LEVEL1, "include/Resources/Sprites/LaserBullets/Bullet.png"},
    {LEVEL2, "include/Resources/Sprites/LaserBullets/Bullet.png"},
    {LEVEL3, "include/Resources/Sprites/LaserBullets/Bullet.png"},
    {LEVEL4, "include/Resources/Sprites/LaserBullets/Bullet.png"},
    {LEVEL5, "include/Resources/Sprites/LaserBullets/Bullet.png"},
};
const std::unordered_map<BulletLevels, unsigned int> resourcePathsBulletsDamage = {
    {LEVEL1, 1},
    {LEVEL2, 1},
    {LEVEL3, 1},
    {LEVEL4, 1},
    {LEVEL5, 1},
};


const std::unordered_map<BulletLevels, std::string> resourcePathsLightningBullets = {
    // Player
    {LEVEL1, "Sinclude/Resources/prites/LaserBullets/LightningLevel1.png"},
    {LEVEL2, "Sinclude/Resources/prites/LaserBullets/LightningLevel2.png"},
    {LEVEL3, "include/Resources/Sprites/LaserBullets/LightningLevel3.png"},
    {LEVEL4, "include/Resources/Sprites/LaserBullets/LightningLevel4.png"},
    {LEVEL5, "include/Resources/Sprites/LaserBullets/LightningLevel5.png"},
};

// Enum for all bullet damage types

const std::unordered_map<BulletLevels, unsigned int> resourcePathsLightningBulletsDamage = {
    {LEVEL1, 1},
    {LEVEL2, 2},
    {LEVEL3, 3},
    {LEVEL4, 4},
    {LEVEL5, 5}};

const std::unordered_map<BulletLevels, std::string> resourcePathsDarkMatterBullet = {
    // Player
    {LEVEL1, "include/Resources/Sprites/LaserBullets/DarkMatterLevel1.png"},
    {LEVEL2, "include/Resources/Sprites/LaserBullets/DarkMatterLevel2.png"},
    {LEVEL3, "include/Resources/Sprites/LaserBullets/DarkMatterLevel3.png"},
    {LEVEL4, "include/Resources/Sprites/LaserBullets/DarkMatterLevel4.png"},
    {LEVEL5, "include/Resources/Sprites/LaserBullets/DarkMatterLevel5.png"},
};

const std::unordered_map<BulletLevels, unsigned int> resourcePathsDarkMatterBulletDamage = {
    {LEVEL1, 2},
    {LEVEL2, 3},
    {LEVEL3, 4},
    {LEVEL4, 5},
    {LEVEL5, 6}};

const std::unordered_map<BulletLevels, std::string> resourcePathsNuclierMaterialBullet = {
    // Player
    {LEVEL1, "include/Resources/Sprites/LaserBullets/NuclierMaterialLevel1.png"},
    {LEVEL2, "include/Resources/Sprites/LaserBullets/NuclierMaterialLevel2.png"},
    {LEVEL3, "include/Resources/Sprites/LaserBullets/NuclierMaterialLevel3.png"},
    {LEVEL4, "include/Resources/Sprites/LaserBullets/NuclierMaterialLevel4.png"},
    {LEVEL5, "include/Resources/Sprites/LaserBullets/NuclierMaterialLevel5.png"},
};

const std::unordered_map<BulletLevels, unsigned int> resourcePathsNuclierMaterialBulletDamage = {
    {LEVEL1, 3},
    {LEVEL2, 4},
    {LEVEL3, 5},
    {LEVEL4, 6},
    {LEVEL5, 7}};

const std::unordered_map<BulletLevels, std::string> resourcePathsPlasmaBullets = {
    // Player
    {LEVEL1, "include/Resources/Sprites/LaserBullets/PlasmaLevel1.png"},
    {LEVEL2, "include/Resources/Sprites/LaserBullets/PlasmaLevel2.png"},
    {LEVEL3, "include/Resources/Sprites/LaserBullets/PlasmaLevel3.png"},
    {LEVEL4, "include/Resources/Sprites/LaserBullets/PlasmaLevel4.png"},
    {LEVEL5, "include/Resources/Sprites/LaserBullets/PlasmaLevel5.png"},
};

const std::unordered_map<BulletLevels, unsigned int> resourcePathsPlasmaBulletsDamage = {
    {LEVEL1, 4},
    {LEVEL2, 5},
    {LEVEL3, 6},
    {LEVEL4, 7},
    {LEVEL5, 8}};

const std::unordered_map<BulletLevels, std::string> resourcePathsPlanetaryBombBullets = {
    // Player
    {LEVEL1, "include/Resources/Sprites/LaserBullets/PlanetaryBombLevel1.png"},
    {LEVEL2, "include/Resources/Sprites/LaserBullets/PlanetaryBombLevel2.png"},
    {LEVEL3, "include/Resources/Sprites/LaserBullets/PlanetaryBombLevel3.png"},
    {LEVEL4, "include/Resources/Sprites/LaserBullets/PlanetaryBombLevel4.png"},
    {LEVEL5, "include/Resources/Sprites/LaserBullets/PlanetaryBombLevel5.png"},
};

const std::unordered_map<BulletLevels, unsigned int> resourcePathsPlanetaryBombBulletsDamage = {
    {LEVEL1, 5},
    {LEVEL2, 6},
    {LEVEL3, 7},
    {LEVEL4, 8},
    {LEVEL5, 9}};

const std::unordered_map<BulletLevels, std::string> resourcePathsPeaShooterBullets = {
    {LEVEL1, "include/Resources/Sprites/LaserBullets/01.png"},
    {LEVEL2, "include/Resources/Sprites/LaserBullets/01.png"},
    {LEVEL3, "include/Resources/Sprites/LaserBullets/01.png"},
    {LEVEL4, "include/Resources/Sprites/LaserBullets/01.png"},
    {LEVEL5, "include/Resources/Sprites/LaserBullets/01.png"},
};
const std::unordered_map<BulletLevels, unsigned int> resourcePathsPeaShooterBulletsDamage = {
    {LEVEL1, 1},
    {LEVEL2, 1},
    {LEVEL3, 1},
    {LEVEL4, 1},
    {LEVEL5, 1},
};

enum ChangingBullets
{
    // Bullets
    LASER_BULLET = 0,
    LIGHTNING_BULLET,
    DARK_MATTER_BULLET,
    NUCLIER_MATERIAL_BULLET,
    PLASMA_BULLET,
    PLANETARY_BOMB_BULLET,

    // Side Gun
    PEA_SHOOTER_BULLET,

    // Total
    NUM_CHANGING_BULLETS
};

const std::unordered_map<ChangingBullets, std::unordered_map<BulletLevels, std::string> > resourcePathsMaps = {
    // Player
    {LASER_BULLET, resourcePathsLaserBullets},
    {LIGHTNING_BULLET, resourcePathsLightningBullets},
    {DARK_MATTER_BULLET, resourcePathsDarkMatterBullet},
    {NUCLIER_MATERIAL_BULLET, resourcePathsNuclierMaterialBullet},
    {PLASMA_BULLET, resourcePathsPlasmaBullets},
    {PLANETARY_BOMB_BULLET, resourcePathsPlanetaryBombBullets},
    {PEA_SHOOTER_BULLET, resourcePathsPeaShooterBullets},
};

const std::unordered_map<ChangingBullets, std::unordered_map<BulletLevels, unsigned int> > resourcePathsDamageMaps = {
    // Player
    {LASER_BULLET, resourcePathsBulletsDamage},
    {LIGHTNING_BULLET, resourcePathsLightningBulletsDamage},
    {DARK_MATTER_BULLET, resourcePathsDarkMatterBulletDamage},
    {NUCLIER_MATERIAL_BULLET, resourcePathsNuclierMaterialBulletDamage},
    {PLASMA_BULLET, resourcePathsPlasmaBulletsDamage},
    {PLANETARY_BOMB_BULLET, resourcePathsPlanetaryBombBulletsDamage},
    {PEA_SHOOTER_BULLET, resourcePathsPeaShooterBulletsDamage},
};