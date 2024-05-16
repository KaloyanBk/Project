#include "../../include/Bullets/LaserBullet.hpp"

LaserBullet::LaserBullet(  Vector2f pos, Vector2f direction,
                float initialVelocity, float maxVelocity,
                float acceleration)
    : Bullet(pos, direction, initialVelocity, maxVelocity, acceleration)
{
    this->setTexture(LASER_BULLET);
    this->setDamage(LASER_BULLET);

    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setScale(Vector2f(0.5f, 0.5f));

}

void LaserBullet::Update()
{
    // Implement LASERBullet specific behavior here
    // For example, adjust position, check for collisions, etc.
    Move();
}
