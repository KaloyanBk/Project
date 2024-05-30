/**
 * @file PeaBullet.cpp
 * @author Kaloyan
 * @brief This is the implementation file for the PeaBullet class, child of Bullet, which is used to create Pea bullets for the player to shoot.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 */

#include "../../include/Bullets/PeaBullet.hpp"

/**
 * @brief Constructs a new PeaBullet object.
 * 
 * @param pos Initial position of the PeaBullet.
 * @param level Level of the PeaBullet.
 * @param direction Direction of the PeaBullet.
 * @param initialVelocity Initial velocity of the PeaBullet.
 * @param maxVelocity Maximum velocity of the PeaBullet.
 * @param acceleration Acceleration of the PeaBullet.
 */
PeaBullet::PeaBullet(Vector2f pos, int level, Vector2f direction,
                       float initialVelocity, float maxVelocity,
                       float acceleration)
    : Bullet(pos, level, direction, initialVelocity, maxVelocity, acceleration)
{
    this->setTexture(PEA_SHOOTER_BULLET, this->level);
    this->setDamage(PEA_SHOOTER_BULLET, this->level);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setScale(Vector2f(0.2f, 0.2f));
}

/**
 * @brief Updates the PeaBullet's movement.
 * 
 * @param dt Time elapsed since the last update.
 */
void PeaBullet::Update(const float &dt)
{
    Move(dt);
}
