#include "../../include/Enemys/Enemy.hpp"

Enemy::Enemy(Texture *texture, Vector2u windowBounds,
             Vector2f position, Vector2f direction,
             Vector2f scale, int type,
             int hpMax, int damageMax, int damageMin)
    : texture(texture), type(type),
      hpMax(hpMax), direction(direction),
      damageMax(damageMax), damageMin(damageMin)
{
    this->sprite.setTexture(*this->texture);
    this->sprite.setScale(scale);

    this->hp = hpMax;

    this->sprite.setPosition(windowBounds.x, rand() % (int)(windowBounds.y - this->sprite.getGlobalBounds().height));

}

Enemy::~Enemy() {}

void Enemy::TakeDamage(int damage)
{
    this->hp -= damage;

    if (this->hp <= 0)
        this->hp = 0;
}

void Enemy::Move()
{
    switch (this->type)
    {
    case MOVE_LEFT:
        this->sprite.move(this->direction.x * 10.f, this->direction.y * 10.f);
        break;
    case FOLLOW:
        break;
    case FOLLOW_FAST:
        break;
    case FOLLOW_SHOOT:
        break;
    default:
        break;
    }
}
void Enemy::Update()
{
    Move();

    // enemy Death
}

void Enemy::Render(sf::RenderTarget &target)
{
    target.draw(sprite);
}
