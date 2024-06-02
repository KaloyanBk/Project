/**
 * @file PeaShooter.cpp
 * @brief This is the implementation file for the PeaShooter class, a child of Weapon, used to create the pea shooter weapon for the player.
 * @author Kaloyan
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 */

#include "../../include/Weapons/PeaShooter.hpp"
#include "../../include/Bullets/PeaBullet.hpp"
#include <iostream>

/**
 * @brief Default constructor for the PeaShooter class.
 */
PeaShooter::PeaShooter()
    : Weapon(), upgradeLevel(0)
{
}

/**
 * @brief Parameterized constructor for the PeaShooter class.
 * 
 * @param level The level of the pea shooter.
 * @param UpOrDown Whether the pea shooter is positioned up or down.
 */
PeaShooter::PeaShooter(int level, int UpOrDown)
    : Weapon(PEA_SHOOTER, level, UpOrDown, 10, 1), upgradeLevel(0)
{
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    sprite.setScale(0.9f, 0.9f);
    this->UpOrDown = UpOrDown;
    this->bulletLevel = level;
    this->level = level;
}

/**
 * @brief Destructor for the PeaShooter class.
 */
PeaShooter::~PeaShooter()
{
    /// Destructor implementation, if needed
}

/**
 * @brief Update method for the PeaShooter class.
 * 
 * @param targetPosition The position of the target.
 * @param bounds The bounds of the pea shooter.
 * @param dt The delta time for updating.
 */
void PeaShooter::Update(Vector2f targetPosition, FloatRect bounds, const float &dt)
{
    Vector2f weaponPositionUp = Vector2f(targetPosition.x + 20.f, targetPosition.y - bounds.width / 2.f + 25.f);
    Vector2f weaponPositionDown = Vector2f(targetPosition.x + 20.f, targetPosition.y + bounds.width / 2.f - 25.f);

    sprite.setPosition((this->UpOrDown == 0) ? weaponPositionUp : weaponPositionDown);
}

/**
 * @brief Fire method for the PeaShooter class.
 * 
 * @param position The position to fire from.
 * @param direction The firing direction.
 * @param scale The scale of the fired object.
 */
void PeaShooter::Fire(const Vector2f &position, const Vector2f &direction, const Vector2f &scale)
{
    Vector2f positionUp = Vector2f(position.x, position.y - 5.f);
    Vector2f positionDown = Vector2f(position.x, position.y + 5.f);

    switch (this->level)
    {
    case 0:
        bullets.push_back(new PeaBullet(position, this->bulletLevel, direction));
        break;
    case 1:
        bullets.push_back(new PeaBullet(positionUp, this->bulletLevel, direction));
        bullets.push_back(new PeaBullet(positionDown, this->bulletLevel, direction));
        break;
    case 2:
        bullets.push_back(new PeaBullet(positionUp, this->bulletLevel, direction));
        bullets.push_back(new PeaBullet(position, this->bulletLevel, direction));
        bullets.push_back(new PeaBullet(positionDown, this->bulletLevel, direction));
        break;
    default:
        break;
    }
}

/**
 * @brief Upgrade method for the PeaShooter class.
 */
void PeaShooter::Upgrade()
{
    Weapon::Upgrade(); 
}
