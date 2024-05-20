#include "../../include/Bullets/PeaBullet.hpp"

PeaBullet::PeaBullet(  Vector2f pos, int level, Vector2f direction,
                float initialVelocity, float maxVelocity,
                float acceleration)
    : Bullet(pos, level, direction, initialVelocity, maxVelocity, acceleration)
{
    this->setTexture(PEA_SHOOTER, this->level);
    this->setDamage(PEA_SHOOTER, this->level);
        this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setScale(Vector2f(0.2f, 0.2f));

}

void PeaBullet::Update(const float &dt)
{
    // Implement LASERBullet specific behavior here
    // For example, adjust position, check for collisions, etc.
    Move(dt);
}
