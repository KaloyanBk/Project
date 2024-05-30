/**
 * @file Follow.cpp
 * @author Kaloyan
 * @brief This is the implementation file for the FollowEnemy class, a subclass of Enemy, used to create enemies that follow the player.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 */

#include "../../include/Enemys/Follow.hpp"
#include <cmath>

/**
 * @brief Constructs a new FollowEnemy object.
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
 * @param playerToFollow Index of the player to follow.
 */
FollowEnemy::FollowEnemy(sf::Texture *texture, sf::Vector2u windowBounds,
                         sf::Vector2f position, sf::Vector2f direction,
                         sf::Vector2f scale, float exp,
                         int hpMax, int damageMax, int damageMin, int playerToFollow)
    : Enemy(texture, windowBounds, position, direction, scale, exp, hpMax, damageMax, damageMin),
      following(true), initialDirection(direction)
{
    this->followTimerMax = 150.f; /// Duration to follow the player
    this->followTimer = 0.f;
    this->enemySpawnTimerMax = 100.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->playerToFollow = playerToFollow;
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);

    this->speedx = 8.f;
    this->speedy = 10.f;
}

/**
 * @brief Destroys the FollowEnemy object.
 */
FollowEnemy::~FollowEnemy() {}

/**
 * @brief Moves the FollowEnemy.
 * 
 * @param dt Time elapsed since the last update.
 * @param playerPosition Position of the player.
 */
void FollowEnemy::Move(float dt, sf::Vector2f playerPosition)
{
    if (this->following)
    {
        if (this->followTimer < this->followTimerMax)
        {
            this->followTimer += 1.f * dt * this->dtMultiplier;

            /// Calculate direction towards the player
            sf::Vector2f directionToPlayer = playerPosition - this->sprite.getPosition();
            float length = sqrt(directionToPlayer.x * directionToPlayer.x + directionToPlayer.y * directionToPlayer.y);

            if (length > 0)
            {
                directionToPlayer /= length; /// Normalize the direction

                /// Calculate the angle to rotate the sprite
                float angle = atan2(directionToPlayer.y, directionToPlayer.x) * 360.f / 3.14159265f;

                if (angle > -360.f && angle < -300.f || angle > 300.f && angle < 360.f)
                {
                    this->sprite.setRotation(angle);
                }

                /// Move towards the player
                float newSpeedx = (speedx) * dt * this->dtMultiplier; /// Adjust speed as needed
                float newSpeedy = (speedy) * dt * this->dtMultiplier; /// Adjust speed as needed
                this->sprite.move(directionToPlayer.x * newSpeedx, directionToPlayer.y * newSpeedy);
            }

            /// Check if the enemy has passed the player
            if ((initialDirection.x > 0 && this->sprite.getPosition().x > playerPosition.x) ||
                (initialDirection.x < 0 && this->sprite.getPosition().x < playerPosition.x) ||
                (initialDirection.y > 0 && this->sprite.getPosition().y > playerPosition.y) ||
                (initialDirection.y < 0 && this->sprite.getPosition().y < playerPosition.y))
            {
                this->following = false;
                this->sprite.setRotation(0.f); /// Reset rotation to face straight
            }
        }
        else
        {
            this->following = false;
        }
    }

    if (!this->following)
    {
        /// Continue moving straight in the initial direction
        this->sprite.move(this->initialDirection.x * speedx * dt * this->dtMultiplier, 0.f);
        if (static_cast<int>(this->sprite.getRotation()) != 0)
        {
            if (this->sprite.getRotation() > 180 && this->sprite.getRotation() < 360)
            {
                this->sprite.rotate(0.05f);
            }
            else if (this->sprite.getRotation() > 0 && this->sprite.getRotation() < 180)
            {
                this->sprite.rotate(-0.05f);
            }
        }
    }
}
