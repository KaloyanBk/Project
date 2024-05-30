/**
 * @file Lightning.cpp
 * @author Kaloyan
 * @brief This is the implementation file for the Lightning class, child of Bullet, which is used to create Lightning bullets for the player to shoot.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 */

#include "../../include/Bullets/Lightning.hpp"

/**
 * @brief Constructs a new Lightning object.
 * 
 * @param pos Initial position of the Lightning.
 * @param level Level of the Lightning.
 * @param direction Direction of the Lightning.
 * @param initialVelocity Initial velocity of the Lightning.
 * @param maxVelocity Maximum velocity of the Lightning.
 * @param acceleration Acceleration of the Lightning.
 */
Lightning::Lightning(Vector2f pos, int level, Vector2f direction,
                     float initialVelocity, float maxVelocity,
                     float acceleration)
    : Bullet(pos, level, direction, initialVelocity, maxVelocity, acceleration)
{
    this->setTexture(LIGHTNING_BULLET, this->level);
    this->setDamage(LIGHTNING_BULLET, this->level);
    
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setScale(Vector2f(0.5f, 0.5f));
}

/**
 * @brief Updates the Lightning's movement.
 * 
 * @param dt Time elapsed since the last update.
 */
void Lightning::Update(const float &dt)
{
    Move(dt);
}
