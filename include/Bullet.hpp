#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;

class Bullet
{
private:
    Sprite sprite;
    Texture* texture;
    Vector2f currentVelocity;
    Vector2f direction;
    float maxVelocity;
    float acceleration;

public:
    Bullet(Texture* texture, Vector2f pos,  Vector2f scale,
           Vector2f direction = Vector2f(1.f, 0.f), float initialVelocity = 2.f,
           float maxVelocity = 50.f, float acceleration = 1.f);
    virtual ~Bullet(); // Define the virtual destructor

    // Accessors
    const FloatRect getBounds() const { return this->sprite.getGlobalBounds(); }
    const Vector2f& getPosition() const { return this->sprite.getPosition(); }

    // Setters

    // Functions
    void Move();
    void Update();
    void Render(RenderTarget& target);
};
