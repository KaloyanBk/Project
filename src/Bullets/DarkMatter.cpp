/**
 * @file DarkMatter.cpp
 * @author Kaloyan
 * @brief This is the implementation file for the DarkMatter class, child of Bullet, which is used to create DarkMatter bullets for the player to shoot.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 */

#include "../../include/Bullets/DarkMatter.hpp"

/**
 * @brief Constructs a new DarkMatter object.
 * 
 * @param pos Initial position of the DarkMatter bullet.
 * @param level Level of the DarkMatter bullet.
 * @param direction Direction of the DarkMatter bullet.
 * @param initialVelocity Initial velocity of the DarkMatter bullet.
 * @param maxVelocity Maximum velocity of the DarkMatter bullet.
 * @param acceleration Acceleration of the DarkMatter bullet.
 */
DarkMatter::DarkMatter(Vector2f pos, int level, Vector2f direction,
                       float initialVelocity, float maxVelocity,
                       float acceleration)
    : Bullet(pos, level,direction, initialVelocity, maxVelocity, acceleration)
{
    this->setTexture(DARK_MATTER_BULLET, this->level);
    this->setDamage(DARK_MATTER_BULLET, this->level);

    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setScale(Vector2f(0.5f, 0.5f));
}

/**
 * @brief Updates the DarkMatter bullet's movement.
 * 
 * @param dt Time elapsed since the last update.
 */
void DarkMatter::Update(const float &dt)
{
    Move(dt);
}
