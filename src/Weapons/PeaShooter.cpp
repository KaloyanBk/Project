#include "../../include/Weapons/PeaShooter.hpp"

PeaShooter::PeaShooter()
    : Weapon(), upgradeLevel(0)
{
    sprite.setScale(0.9f, 0.9f);
}

PeaShooter::PeaShooter(Texture *weaponTexture, Texture *bulletTexture, int UpOrDown)
    : Weapon(weaponTexture, bulletTexture, UpOrDown, 10, 1), upgradeLevel(0)
{
    sprite.setScale(0.9f, 0.9f);
}

PeaShooter::~PeaShooter()
{
    // Destructor implementation, if needed
}

void PeaShooter::Update(Vector2f targetPosition, FloatRect bounds)
{
    Vector2f weaponPositionUp = Vector2f(targetPosition.x + 20.f, targetPosition.y + bounds.width / 2.f - 30.f);
    Vector2f weaponPositionDown = Vector2f(targetPosition.x + 20.f, targetPosition.y - bounds.width / 2.f + 30.f);

    sprite.setPosition((UpOrDown == 0) ? weaponPositionUp : weaponPositionDown);
}

void PeaShooter::Fire(const Vector2f &position, const Vector2f &direction, const Vector2f &scale)
{
    // Create a new bullet
    Bullet bullet = Bullet(bulletTexture,
                           position, scale, direction,
                           5.f, 10.f, 0.f);
                           
    bullets.push_back(bullet);
}

void PeaShooter::Upgrade()
{
    Weapon::Upgrade(); // Call base class upgrade method
}
