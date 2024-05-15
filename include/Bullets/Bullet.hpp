#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "../Resources/BulletTextures.hpp"

using namespace sf;

class Bullet
{
protected:
    Sprite sprite;
    Texture *texture;
    Vector2f currentVelocity;
    Vector2f direction;
    float maxVelocity;
    float acceleration;

    int damage;
    int damageMax;

public:
    Bullet(Vector2f pos, Vector2f direction = Vector2f(1.f, 0.f),
                float initialVelocity = 2.f, float maxVelocity = 50.f,
                float acceleration = 1.f);
    virtual ~Bullet();

    // Accessors
    const FloatRect getBounds() const { return this->sprite.getGlobalBounds(); }
    const Vector2f &getPosition() const { return this->sprite.getPosition(); }

    // Setters
    void setTexture(int type);
    void setDamage(int damage);


    // Functions

    virtual void Move();
    virtual void Update();
    void Render(RenderTarget &target);
};
