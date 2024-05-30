/**
 * @file Enemy.hpp
 * @author Kaloyan
 * @brief This is the header file for the Enemy class, which is used to create enemies for the player to fight against.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include "../Bullets/Bullet.hpp"
#include "../Resources/Fonts.hpp"
#include "../Resources/Textures.hpp"
#include "../Player.hpp"

class Enemy
{
protected:
    float dtMultiplier;
    sf::Sprite sprite;
    sf::Texture *texture;
    sf::Vector2f direction;
    sf::Vector2u windowBounds;

    float damageTimer;
    float damageTimerMax;

    int hp;
    int hpMax;
    int damageMin;
    int damageMax;

    float exp;

    int enemySpawnTimer;
    int enemySpawnTimerMax;

    int playerToFollow = 0;

    float speedx;
    float speedy;

public:
    Enemy(sf::Texture *texture, sf::Vector2u windowBounds,
          sf::Vector2f position, sf::Vector2f direction,
          sf::Vector2f scale, float exp,
          int hpMax, int damageMax, int damageMin);
    virtual ~Enemy();

    // Accessors
    inline const int getDamage() const { return rand() % this->damageMax + this->damageMin; }
    inline const int getHp() const { return this->hp; }
    inline const int getHpMax() const { return this->hpMax; }
    inline const float getExp() const { return this->exp; }
    inline const bool isDead() const { return this->hp <= 0; }

    inline const sf::FloatRect getBounds() const { return this->sprite.getGlobalBounds(); }
    inline const sf::Vector2f &getPosition() const { return this->sprite.getPosition(); }
    inline const int getPlayerToFollow() const { return this->playerToFollow; }

    // Functions
    void TakeDamage(int damage);
    virtual void Move(float dt, Vector2f playerPosition) = 0;
    virtual void Update(float dt, Vector2f playerPosition);
    void Render(sf::RenderTarget &target);
};

enum enemyTypes
{
    MOVE_LEFT = 0,
    FOLLOW,
    FOLLOW_FAST,
    FOLLOW_SHOOT,
};
