#include "../../include/Weapons/PeaShooter.hpp"
#include "../../include/Bullets/PeaBullet.hpp"

PeaShooter::PeaShooter()
    : Weapon(), upgradeLevel(0)
{}

PeaShooter::PeaShooter(Texture *weaponTexture, int UpOrDown)
    : Weapon(weaponTexture, UpOrDown, 10, 1), upgradeLevel(0)
{

}

PeaShooter::~PeaShooter()
{
    // Destructor implementation, if needed
}

void PeaShooter::Update(Vector2f targetPosition, FloatRect bounds, const float &dt)
{
    Vector2f weaponPositionUp = Vector2f(targetPosition.x + 20.f , targetPosition.y - bounds.width / 2.f + 30.f );
    Vector2f weaponPositionDown = Vector2f(targetPosition.x + 20.f , targetPosition.y + bounds.width / 2.f - 30.f );

    sprite.setPosition((this->UpOrDown == 0) ? weaponPositionUp : weaponPositionDown);
}

void PeaShooter::Fire(const Vector2f &position, const Vector2f &direction, const Vector2f &scale)
{
    // Create a new bullet
    Vector2f positionUp = Vector2f(position.x, position.y - 5.f);
    Vector2f positionDown = Vector2f(position.x, position.y + 5.f);

    bullets.push_back(new PeaBullet(positionUp, direction));
    bullets.push_back(new PeaBullet(position, direction));
    bullets.push_back(new PeaBullet(positionDown, direction));
}

void PeaShooter::Upgrade()
{
    Weapon::Upgrade(); // Call base class upgrade method
}
