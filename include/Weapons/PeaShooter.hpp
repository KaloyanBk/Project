#pragma once

#include "Weapon.hpp"

class PeaShooter : public Weapon
{
private:
    int upgradeLevel;

public:
    // Constructors/Destructors
    PeaShooter();
    PeaShooter(Texture *weaponTexture, Texture *bulletTexture, int UpOrDown);
    virtual ~PeaShooter();

    // Accessors
    Texture *getBulletTexture() const { return bulletTexture; }

    // Functions
    void Update(Vector2f targetPosition, FloatRect bounds) override;
    void Fire(const Vector2f &position, const Vector2f &direction, const Vector2f &scale) override;
    void Upgrade() override;
};
