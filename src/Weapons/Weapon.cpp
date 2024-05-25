#include "../../include/Weapons/Weapon.hpp"
#include <iostream>

Weapon::Weapon()
    : fireRate(0), fireRateMax(10), weaponTexture(nullptr),
      bulletLevel(1), damage(1), damageMax(2)
{
}

Weapon::Weapon(int type, int level, int UpOrDown, int fireRateMax, int damageMax)
    : fireRate(0), fireRateMax(fireRateMax),
      bulletLevel(level), damage(1), damageMax(damageMax), UpOrDown(UpOrDown)
{
    this->dtMultiplier = 60.f;
    weaponTexture = new sf::Texture();

    switch (UpOrDown)
    {
    case 0:
    
        if (!this->weaponTexture->loadFromFile(SideGunsUp.at(static_cast<SideGuns>(type)).at(static_cast<Levels>((level)))))
        {
            std::cerr << "Failed to load texture: " << SideGunsUp.at(static_cast<SideGuns>(PEA_SHOOTER)).at(static_cast<Levels>((SIDE_GUN_LEVEL1))) << std::endl;
        }
        break;
    case 1:
        std::cout << "Type: " << type << " Level: " << level << std::endl;
        if (!this->weaponTexture->loadFromFile(SideGunsDown.at(static_cast<SideGuns>(type)).at(static_cast<Levels>((level)))))
        {
            std::cerr << "Failed to load texture: " << SideGunsDown.at(static_cast<SideGuns>(type)).at(static_cast<Levels>((level))) << std::endl;
        }
        break;
    default:
        break;
    }

    this->sprite.setTexture(*this->weaponTexture);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
}

Weapon::~Weapon() {}

void Weapon::Update(Vector2f targetPosition, FloatRect bounds, const float &dt)
{
}

void Weapon::Fire(const Vector2f &position, const Vector2f &direction, const Vector2f &scale)
{
}

void Weapon::Upgrade()
{
    damage++;
    fireRateMax -= 2;
}

void Weapon::Render(RenderTarget &target)
{
    // Render bullets
    for (size_t i = 0; i < bullets.size(); i++)
    {
        bullets[i]->Render(target);
    }

    // Render the weapon
    target.draw(sprite);
}
