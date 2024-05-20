#include "../../include/Bullets/DarkMatter.hpp"

DarkMatter::DarkMatter(Vector2f pos, int level, Vector2f direction,
                       float initialVelocity, float maxVelocity,
                       float acceleration)
    : Bullet(pos, level,direction, initialVelocity, maxVelocity, acceleration)
{
    this->setTexture(DARK_MATTER_BULLET, this->level);
    this->setDamage(DARK_MATTER_BULLET, this->level);

    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setScale(Vector2f(0.5f, 0.5f));
}

void DarkMatter::Update(const float &dt)
{
    // Implement LASERBullet specific behavior here
    // For example, adjust position, check for collisions, etc.
    Move(dt);
}
