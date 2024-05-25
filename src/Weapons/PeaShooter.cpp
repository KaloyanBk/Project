#include "../../include/Weapons/PeaShooter.hpp"
#include "../../include/Bullets/PeaBullet.hpp"
#include <iostream>

PeaShooter::PeaShooter()
    : Weapon(), upgradeLevel(0)
{
}

PeaShooter::PeaShooter(int level, int UpOrDown)
    : Weapon(PEA_SHOOTER, level, UpOrDown, 10, 1), upgradeLevel(0)
{

    // Load the weapon texture
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    sprite.setScale(0.9f, 0.9f);
    this->UpOrDown = UpOrDown;
    this->bulletLevel = level;
    this->level = level;
}

PeaShooter::~PeaShooter()
{
    // Destructor implementation, if needed
}

void PeaShooter::Update(Vector2f targetPosition, FloatRect bounds, const float &dt)
{
    Vector2f weaponPositionUp = Vector2f(targetPosition.x + 20.f, targetPosition.y - bounds.width / 2.f + 25.f);
    Vector2f weaponPositionDown = Vector2f(targetPosition.x + 20.f, targetPosition.y + bounds.width / 2.f - 25.f);

    sprite.setPosition((this->UpOrDown == 0) ? weaponPositionUp : weaponPositionDown);
}

void PeaShooter::Fire(const Vector2f &position, const Vector2f &direction, const Vector2f &scale)
{
    // Create a new bullet
    Vector2f positionUp = Vector2f(position.x, position.y - 5.f);
    Vector2f positionDown = Vector2f(position.x, position.y + 5.f);

    switch (this->level)
    {
    case 0:
        bullets.push_back(new PeaBullet(position, this->bulletLevel, direction));
        break;
    case 1:
        bullets.push_back(new PeaBullet(positionUp, this->bulletLevel, direction));
        bullets.push_back(new PeaBullet(positionDown, this->bulletLevel, direction));
        break;
    case 2:
        bullets.push_back(new PeaBullet(positionUp, this->bulletLevel, direction));
        bullets.push_back(new PeaBullet(position, this->bulletLevel, direction));
        bullets.push_back(new PeaBullet(positionDown, this->bulletLevel, direction));
        break;
    default:
        break;
    }
}

void PeaShooter::Upgrade()
{
    Weapon::Upgrade(); // Call base class upgrade method
}
