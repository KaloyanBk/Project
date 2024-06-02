/**
 * @file PeaShooter.hpp
 * @author Kaloyan
 * @brief This is the header file for the PeaShooter class, child of Weapon, which is used to create PeaShooter weapons for the player to shoot.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include "Weapon.hpp"


class PeaShooter : public Weapon
{
private:
    int upgradeLevel;
    int level;

public:
    PeaShooter();
    PeaShooter(int level, int UpOrDown);
    virtual ~PeaShooter();


    // Functions
    void Update(Vector2f targetPosition, FloatRect bounds, const float &dt) override;
    void Fire(const Vector2f &position, const Vector2f &direction, const Vector2f &scale) override;
    void Upgrade() override;

};
