#pragma once

#include "Bullet.hpp"

class LaserBullet : public Bullet
{
public:
    LaserBullet(Vector2f pos, Vector2f direction = Vector2f(1.f, 0.f),
                float initialVelocity = 2.f, float maxVelocity = 50.f,
                float acceleration = 1.f);

    void Update() override;
};
