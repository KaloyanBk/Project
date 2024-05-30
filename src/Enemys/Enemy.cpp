/**
 * @file Enemy.cpp
 * @author Kaloyan
 * @brief This is the implementation file for the Enemy class, which is used to create enemies for the player to fight against.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 */

#include "../../include/Enemys/Enemy.hpp"

/**
 * @brief Constructs a new Enemy object.
 * 
 * @param texture Pointer to the texture for the enemy.
 * @param windowBounds The bounds of the game window.
 * @param position Initial position of the enemy.
 * @param direction Initial movement direction of the enemy.
 * @param scale Scale factor for the enemy sprite.
 * @param exp Experience points gained when defeating the enemy.
 * @param hpMax Maximum hit points of the enemy.
 * @param damageMax Maximum damage inflicted by the enemy.
 * @param damageMin Minimum damage inflicted by the enemy.
 */
Enemy::Enemy(sf::Texture *texture, sf::Vector2u windowBounds,
             sf::Vector2f position, sf::Vector2f direction,
             sf::Vector2f scale, float exp,
             int hpMax, int damageMax, int damageMin)
    : texture(texture), exp(exp),
      hpMax(hpMax), direction(direction),
      damageMax(damageMax), damageMin(damageMin)
{
    this->dtMultiplier = 60.f;
    this->sprite.setTexture(*this->texture);
    this->sprite.setScale(scale);

    this->damageTimerMax = 3.f;
    this->damageTimer = 0.f;

    this->hp = hpMax;

    this->sprite.setPosition(windowBounds.x, rand() % (int)(windowBounds.y - this->sprite.getGlobalBounds().height));
}

/**
 * @brief Destroys the Enemy object.
 */
Enemy::~Enemy() {}

/**
 * @brief Inflicts damage on the enemy.
 * 
 * @param damage Amount of damage to be inflicted.
 */
void Enemy::TakeDamage(int damage)
{
    this->hp -= damage;
    this->damageTimer = this->damageTimerMax;

    if (this->hp <= 0)
    {
        this->hp = 0;
    }
}

/**
 * @brief Updates the state of the enemy.
 * 
 * @param dt Time elapsed since the last update.
 * @param playerPosition Position of the player.
 */
void Enemy::Update(float dt, Vector2f playerPosition)
{
    Move(dt, playerPosition);
    if (this->damageTimer > 0.f)
    {
        this->damageTimer -= 1.f * dt * this->dtMultiplier;
        this->sprite.setColor(sf::Color::Red);
        this->sprite.move(10.f * this->damageTimer * dt * this->dtMultiplier, 0.f);
    }
    else
    {
        this->sprite.setColor(sf::Color::White);
    }
}

/**
 * @brief Renders the enemy on the screen.
 * 
 * @param target The render target.
 */
void Enemy::Render(sf::RenderTarget &target)
{
    target.draw(sprite);
}
