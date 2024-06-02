/**
 * @file Bullet.cpp
 * @author Kaloyan
 * @brief This is the implementation file for the Bullet class, which is used to create bullets for the player to shoot.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 */

#include "../../include/Bullets/Bullet.hpp"
#include <iostream>

/**
 * @brief Constructs a new Bullet object.
 * 
 * @param pos Initial position of the bullet.
 * @param level Level of the bullet.
 * @param direction Direction of the bullet.
 * @param initialVelocity Initial velocity of the bullet.
 * @param maxVelocity Maximum velocity of the bullet.
 * @param acceleration Acceleration of the bullet.
 */
Bullet::Bullet(Vector2f pos, int level, Vector2f direction,
               float initialVelocity, float maxVelocity,
               float acceleration)
    : direction(direction), currentVelocity(initialVelocity * direction), level(level),
      maxVelocity(maxVelocity), acceleration(acceleration)
{
    this->dtMultiplier = 60.f;

    this->sprite.setPosition(pos - Vector2f(0.f, this->sprite.getGlobalBounds().height / 2));
    this->texture = new Texture();
}

Bullet::~Bullet()
{
    delete this->texture;
}

/**
 * @brief Sets the texture of the bullet based on its type and level.
 * 
 * @param type Type of the bullet.
 * @param level Level of the bullet.
 */
void Bullet::setTexture(int type, int level)
{

    if (!this->texture->loadFromFile(resourcePathsMaps.at(static_cast<ChangingBullets>(type)).at(static_cast<BulletLevels>((level)))))
    {
        std::cerr << "Failed to load texture: " << resourcePathsMaps.at(static_cast<ChangingBullets>(type)).at(static_cast<BulletLevels>((level))) << std::endl;
    }

    this->sprite.setTexture(*this->texture);
}

/**
 * @brief Sets the damage of the bullet based on its type and level.
 * 
 * @param type Type of the bullet.
 * @param level Level of the bullet.
 */
void Bullet::setDamage(int type, int level)
{

    this->damage = resourcePathsDamageMaps.at(static_cast<ChangingBullets>(type)).at(static_cast<BulletLevels>(level));
}

/**
 * @brief Moves the bullet based on its current velocity.
 * 
 * @param dt Time elapsed since the last update.
 */
void Bullet::Move(const float &dt)
{
    if (this->acceleration > 0.f)
    {
        if (this->currentVelocity.x < this->maxVelocity)
            this->currentVelocity.x += this->acceleration * this->direction.x * dt * this->dtMultiplier;

        if (this->currentVelocity.y < this->maxVelocity)
            this->currentVelocity.y += this->acceleration * this->direction.y * dt * this->dtMultiplier;
    }
    else
    {
        this->currentVelocity = Vector2f(this->maxVelocity * this->direction.x * dt * this->dtMultiplier, this->maxVelocity * this->direction.y * dt * this->dtMultiplier);
    }

    this->sprite.move(this->currentVelocity * dt * this->dtMultiplier);
}

/**
 * @brief Updates the bullet's movement.
 * 
 * @param dt Time elapsed since the last update.
 */
void Bullet::Update(const float &dt)
{
    this->Move(dt);
}

/**
 * @brief Renders the bullet on the target.
 * 
 * @param target The render target.
 */
void Bullet::Render(RenderTarget &target)
{
    target.draw(this->sprite);
}
