#include "../../include/Bullets/DarkMatter.hpp"

DarkMatter::DarkMatter( Vector2f pos, Vector2f direction,
                float initialVelocity, float maxVelocity,
                float acceleration)
    : Bullet(pos, direction, initialVelocity, maxVelocity, acceleration)
{
    this->setTexture(DARK_MATTER_BULLET);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setScale(Vector2f(0.1f, 0.1f));

}

void DarkMatter::Update()
{
    // Implement LASERBullet specific behavior here
    // For example, adjust position, check for collisions, etc.
    Move();
}
