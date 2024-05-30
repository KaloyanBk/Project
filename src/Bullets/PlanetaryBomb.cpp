/**
 * @file PlanetaryBomb.cpp
 * @author Kaloyan
 * @brief This is the implementation file for the PlanetaryBomb class, child of Bullet, which is used to create PlanetaryBomb bullets for the player to shoot.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 */

#include "../../include/Bullets/PlanetaryBomb.hpp"

/**
 * @brief Constructs a new PlanetaryBomb object.
 * 
 * @param pos Initial position of the PlanetaryBomb.
 * @param level Level of the PlanetaryBomb.
 * @param direction Direction of the PlanetaryBomb.
 * @param initialVelocity Initial velocity of the PlanetaryBomb.
 * @param maxVelocity Maximum velocity of the PlanetaryBomb.
 * @param acceleration Acceleration of the PlanetaryBomb.
 */
PlanetaryBomb::PlanetaryBomb(Vector2f pos, int level, Vector2f direction,
                             float initialVelocity, float maxVelocity,
                             float acceleration)
    : Bullet(pos, level, direction, initialVelocity, maxVelocity, acceleration)
{
    this->setTexture(PLANETARY_BOMB_BULLET, this->level);
    this->setDamage(PLANETARY_BOMB_BULLET, this->level);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setScale(Vector2f(0.5f, 0.5f));
}

/**
 * @brief Updates the PlanetaryBomb's movement.
 * 
 * @param dt Time elapsed since the last update.
 */
void PlanetaryBomb::Update(const float &dt)
{
    Move(dt);
}
