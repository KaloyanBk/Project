/**
 * @file LaserBullet.cpp
 * @author Kaloyan
 * @brief This is the implementation file for the LaserBullet class, child of Bullet, which is used to create Laser bullets for the player to shoot.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 */

#include "../../include/Bullets/LaserBullet.hpp"

/**
 * @brief Constructs a new LaserBullet object.
 * 
 * @param pos Initial position of the LaserBullet.
 * @param level Level of the LaserBullet.
 * @param direction Direction of the LaserBullet.
 * @param initialVelocity Initial velocity of the LaserBullet.
 * @param maxVelocity Maximum velocity of the LaserBullet.
 * @param acceleration Acceleration of the LaserBullet.
 */
LaserBullet::LaserBullet(Vector2f pos, int level, Vector2f direction,
                float initialVelocity, float maxVelocity,
                float acceleration)
    : Bullet(pos, level, direction, initialVelocity, maxVelocity, acceleration)
{
    this->setTexture(LASER_BULLET, this->level);
    this->setDamage(LASER_BULLET, this->level);

    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setScale(Vector2f(0.5f, 0.5f));

}

/**
 * @brief Updates the LaserBullet's movement.
 * 
 * @param dt Time elapsed since the last update.
 */
void LaserBullet::Update(const float &dt)
{
    Move(dt);
}
