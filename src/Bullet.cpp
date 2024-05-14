#include "../include/Bullet.hpp"

Bullet::Bullet(Texture* texture, Vector2f pos,  Vector2f scale,
               Vector2f direction, float initialVelocity,
               float maxVelocity, float acceleration)
    : direction(direction), currentVelocity(initialVelocity * direction),
      maxVelocity(maxVelocity), acceleration(acceleration)
{
    this->texture = texture;
    this->sprite.setTexture(*this->texture);
    this->sprite.setScale(scale);

    this->sprite.setPosition(pos - Vector2f(0.f, this->sprite.getGlobalBounds().height / 2));
}

Bullet::~Bullet() {}

void Bullet::Move()
{
    if (this->acceleration > 0.f)
    {
        if (this->currentVelocity.x < this->maxVelocity)
            this->currentVelocity.x += this->acceleration * this->direction.x;

        if (this->currentVelocity.y < this->maxVelocity)
            this->currentVelocity.y += this->acceleration * this->direction.y;
    }
    else
    {
        this->currentVelocity = Vector2f(this->maxVelocity * this->direction.x, this->maxVelocity * this->direction.y);
    }

    this->sprite.move(this->currentVelocity);
}

void Bullet::Update()
{
    this->Move();
}

void Bullet::Render(RenderTarget& target)
{
    target.draw(this->sprite);
}
