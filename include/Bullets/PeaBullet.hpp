#pragma once

#include "Bullet.hpp"

class PeaBullet : public Bullet {
public:
    PeaBullet(Vector2f pos, int level,Vector2f direction = Vector2f(1.f, 0.f),
                float initialVelocity = 5.f, float maxVelocity = 10.f,
                float acceleration = 1.f);
    
    void Update(const float &dt) override;
};
