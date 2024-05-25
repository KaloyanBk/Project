#include "../../include/Enemys/MoveLeft.hpp"


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

MoveLeftEnemy::~MoveLeftEnemy() {}

void MoveLeftEnemy::Move(float dt,  Vector2f playerPosition)
{
    this->sprite.move(this->direction.x * speedx * dt * this->dtMultiplier, 0.f);
}

