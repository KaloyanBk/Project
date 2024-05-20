#pragma once

#include "Weapon.hpp"

class PeaShooter : public Weapon
{
private:
    int upgradeLevel;

public:
    // Constructors/Destructors
    PeaShooter();
    PeaShooter(Texture *weaponTexture, int level, int UpOrDown);
    virtual ~PeaShooter();


    // Functions
    void Update(Vector2f targetPosition, FloatRect bounds, const float &dt) override;
    void Fire(const Vector2f &position, const Vector2f &direction, const Vector2f &scale) override;
    void Upgrade() override;
};
