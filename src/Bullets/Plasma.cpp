/**
 * @file Plasma.cpp
 * @author Kaloyan
 * @brief This is the implementation file for the Plasma class, child of Bullet, which is used to create Plasma bullets for the player to shoot.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 */

#include "../../include/Bullets/Plasma.hpp"

/**
 * @brief Constructs a new Plasma object.
 * 
 * @param pos Initial position of the Plasma bullet.
 * @param level Level of the Plasma bullet.
 * @param direction Direction of the Plasma bullet.
 * @param initialVelocity Initial velocity of the Plasma bullet.
 * @param maxVelocity Maximum velocity of the Plasma bullet.
 * @param acceleration Acceleration of the Plasma bullet.
 */
Plasma::Plasma(Vector2f pos, int level, Vector2f direction,
               float initialVelocity, float maxVelocity,
               float acceleration)
    : Bullet(pos, level, direction, initialVelocity, maxVelocity, acceleration)
{
    this->setTexture(PLASMA_BULLET, this->level);
    this->setDamage(PLASMA_BULLET, this->level);

    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setScale(Vector2f(0.5f, 0.5f));
}

/**
 * @brief Updates the Plasma bullet's movement.
 * 
 * @param dt Time elapsed since the last update.
 */
void Plasma::Update(const float &dt)
{
    Move(dt);
}
