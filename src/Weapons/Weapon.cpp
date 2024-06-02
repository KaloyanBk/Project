/**
 * @file Weapon.cpp
 * @author Kaloyan
 * @brief This is the implementation file for the Weapon class, which is used to create weapons for the player.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "../../include/Weapons/Weapon.hpp"
#include <iostream>


Weapon::Weapon()
    : fireRate(0), fireRateMax(10), weaponTexture(nullptr),
      bulletLevel(1), damage(1), damageMax(2)
{
}

/**
 * @brief Parameterized constructor for the Weapon class.
 * 
 * @param type The type of weapon.
 * @param level The level of the weapon.
 * @param UpOrDown Whether the weapon is positioned up or down.
 * @param fireRateMax The maximum fire rate of the weapon.
 * @param damageMax The maximum damage of the weapon.
 */
Weapon::Weapon(int type, int level, int UpOrDown, int fireRateMax, int damageMax)
    : fireRate(0), fireRateMax(fireRateMax),
      bulletLevel(level), damage(1), damageMax(damageMax), UpOrDown(UpOrDown)
{
    this->dtMultiplier = 60.f;
    weaponTexture = new sf::Texture();

    switch (UpOrDown)
    {
    case 0:
        if (!this->weaponTexture->loadFromFile(SideGunsUp.at(static_cast<SideGuns>(type)).at(static_cast<Levels>((level)))))
        {
            std::cerr << "Failed to load texture: " << SideGunsUp.at(static_cast<SideGuns>(PEA_SHOOTER)).at(static_cast<Levels>((SIDE_GUN_LEVEL1))) << std::endl;
        }
        break;
    case 1:
        if (!this->weaponTexture->loadFromFile(SideGunsDown.at(static_cast<SideGuns>(type)).at(static_cast<Levels>((level)))))
        {
            std::cerr << "Failed to load texture: " << SideGunsDown.at(static_cast<SideGuns>(type)).at(static_cast<Levels>((level))) << std::endl;
        }
        break;
    default:
        break;
    }

    this->sprite.setTexture(*this->weaponTexture);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
}

Weapon::~Weapon() {}

/**
 * @brief Update method for the Weapon class.
 * 
 * @param targetPosition The position of the target.
 * @param bounds The bounds of the weapon.
 * @param dt The delta time for updating.
 */
void Weapon::Update(Vector2f targetPosition, FloatRect bounds, const float &dt)
{
}

/**
 * @brief Fire method for the Weapon class.
 * 
 * @param position The position to fire from.
 * @param direction The firing direction.
 * @param scale The scale of the fired object.
 */
void Weapon::Fire(const Vector2f &position, const Vector2f &direction, const Vector2f &scale)
{
}

/**
 * @brief Upgrade method for the Weapon class.
 * 
 * Increases the damage and reduces the fire rate.
 */
void Weapon::Upgrade()
{
    damage++;
    fireRateMax -= 2;
}

/**
 * @brief Render method for the Weapon class.
 * 
 * Renders the weapon and its bullets.
 * 
 * @param target The render target.
 */
void Weapon::Render(RenderTarget &target)
{
    /// Render bullets
    for (size_t i = 0; i < bullets.size(); i++)
    {
        bullets[i]->Render(target);
    }

    /// Render the weapon
    target.draw(sprite);
}