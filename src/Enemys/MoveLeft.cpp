/**
 * @file MoveLeft.cpp
 * @author Kaloyan
 * @brief This is the implementation file for the MoveLeftEnemy class, a subclass of Enemy, used to create enemies that move left.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 */

#include "../../include/Enemys/MoveLeft.hpp"

/**
 * @brief Constructs a new MoveLeftEnemy object.
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
MoveLeftEnemy::MoveLeftEnemy(sf::Texture *texture, sf::Vector2u windowBounds,
                             sf::Vector2f position, sf::Vector2f direction,
                             sf::Vector2f scale, float exp,
                             int hpMax, int damageMax, int damageMin)
    : Enemy(texture, windowBounds, position, direction, scale, exp, hpMax, damageMax, damageMin)
{
    this->enemySpawnTimerMax = 100.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->speedx = 8.f;
    this->speedy = 0.f;
}

/**
 * @brief Destroys the MoveLeftEnemy object.
 */
MoveLeftEnemy::~MoveLeftEnemy() {}

/**
 * @brief Moves the MoveLeftEnemy.
 * 
 * @param dt Time elapsed since the last update.
 * @param playerPosition Position of the player.
 */
void MoveLeftEnemy::Move(float dt, Vector2f playerPosition)
{
    this->sprite.move(this->direction.x * speedx * dt * this->dtMultiplier, 0.f);
}
