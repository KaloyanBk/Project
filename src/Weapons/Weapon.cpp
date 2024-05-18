#include "../../include/Weapons/Weapon.hpp"

Weapon::Weapon()
    : fireRate(0), fireRateMax(10), weaponTexture(nullptr),
      level(1), damage(1), damageMax(2)
{}

Weapon::Weapon(Texture* weaponTexture, int UpOrDown, int fireRateMax, int damageMax)
    : fireRate(0), fireRateMax(fireRateMax), weaponTexture(weaponTexture),
      level(1), damage(1), damageMax(damageMax), UpOrDown(UpOrDown)
{
    this->dtMultiplier = 60.f;

    sprite.setTexture(*weaponTexture);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
}

Weapon::~Weapon() {}

void Weapon::Update(Vector2f targetPosition, FloatRect bounds, const float &dt)
{
}

void Weapon::Fire(const Vector2f& position, const Vector2f& direction, const Vector2f& scale)
{
}

void Weapon::Upgrade()
{
    damage++;
    fireRateMax -= 2;
}

void Weapon::Render(RenderTarget& target)
{
    // Render bullets
    for (size_t i = 0; i < bullets.size(); i++)
    {
        bullets[i]->Render(target);
    }
   
    // Render the weapon
    target.draw(sprite);
}
