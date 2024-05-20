#include "../../include/Bullets/Bullet.hpp"
#include <iostream>

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

void Bullet::setTexture(int type, int level)
{

    if (!this->texture->loadFromFile(resourcePathsMaps.at(static_cast<ChangingBullets>(type)).at(static_cast<BulletLevels>((level)))))
    {
        std::cerr << "Failed to load texture: " << resourcePathsMaps.at(static_cast<ChangingBullets>(type)).at(static_cast<BulletLevels>((level))) << std::endl;
    }

    this->sprite.setTexture(*this->texture);
}

void Bullet::setDamage(int type, int level)
{

    this->damage = resourcePathsDamageMaps.at(static_cast<ChangingBullets>(type)).at(static_cast<BulletLevels>(level));
}

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

void Bullet::Update(const float &dt)
{
    this->Move(dt);
}

void Bullet::Render(RenderTarget &target)
{
    target.draw(this->sprite);
}
