#include "../../include/Enemys/Enemy.hpp"

// Base Enemy class implementation
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

Enemy::~Enemy() {}

void Enemy::TakeDamage(int damage)
{
    this->hp -= damage;
    this->damageTimer = this->damageTimerMax;

    if (this->hp <= 0)
    {
        this->hp = 0;
    }
}

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

void Enemy::Render(sf::RenderTarget &target)
{
    target.draw(sprite);
}
