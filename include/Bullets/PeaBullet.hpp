/**
 * @file PeaBullet.hpp
 * @author Kaloyan
 * @brief This is the header file for the PeaBullet class, child of Bullet, which is used to create Pea bullets for the player to shoot.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include "Bullet.hpp"

class PeaBullet : public Bullet {
public:
    PeaBullet(Vector2f pos, int level,Vector2f direction = Vector2f(1.f, 0.f),
                float initialVelocity = 5.f, float maxVelocity = 10.f,
                float acceleration = 1.f);
    
    void Update(const float &dt) override;
};
