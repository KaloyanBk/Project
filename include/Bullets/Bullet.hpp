/**
 * @file Bullet.hpp
 * @author Kaloyan
 * @brief This is the header file for the Bullet class, which is used to create bullets for the player to shoot.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include "../Resources/BulletResources.hpp"
#include "../TextTag.hpp"

class Bullet
{
protected:
    float dtMultiplier;

    Sprite sprite;
    Texture *texture;
    Vector2f currentVelocity;
    Vector2f direction;
    float maxVelocity;
    float acceleration;

    int damage;
    int damageMax;

    int level;

public:
    Bullet(Vector2f pos, int level,Vector2f direction = Vector2f(1.f, 0.f),
                float initialVelocity = 2.f, float maxVelocity = 50.f,
                float acceleration = 1.f);
    virtual ~Bullet();

    // Accessors
    const FloatRect getBounds() const { return this->sprite.getGlobalBounds(); }
    const Vector2f &getPosition() const { return this->sprite.getPosition(); }
    const int &getDamage() const { return this->damage; }

    // Setters
    void setTexture(int type, int level);
    void setDamage(int damage, int level);

    // Functions

    virtual void Move(const float &dt);
    virtual void Update(const float &dt);
    void Render(RenderTarget &target);
};
