/**
 * @file NuclierMaterial.cpp
 * @author Kaloyan
 * @brief This is the implementation file for the NuclierMaterial class, child of Bullet, which is used to create NuclierMaterial bullets for the player to shoot.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 */

#include "../../include/Bullets/NuclierMaterial.hpp"

/**
 * @brief Constructs a new NuclierMaterial object.
 * 
 * @param pos Initial position of the NuclierMaterial.
 * @param level Level of the NuclierMaterial.
 * @param direction Direction of the NuclierMaterial.
 * @param initialVelocity Initial velocity of the NuclierMaterial.
 * @param maxVelocity Maximum velocity of the NuclierMaterial.
 * @param acceleration Acceleration of the NuclierMaterial.
 */
NuclierMaterial::NuclierMaterial(Vector2f pos, int level, Vector2f direction,
                                 float initialVelocity, float maxVelocity,
                                 float acceleration)
    : Bullet(pos, level, direction, initialVelocity, maxVelocity, acceleration)
{
    this->setTexture(NUCLIER_MATERIAL_BULLET, this->level);
    this->setDamage(NUCLIER_MATERIAL_BULLET, this->level);

    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setScale(Vector2f(0.5f, 0.5f));
}

/**
 * @brief Updates the NuclierMaterial's movement.
 * 
 * @param dt Time elapsed since the last update.
 */
void NuclierMaterial::Update(const float &dt)
{
    Move(dt);
}
