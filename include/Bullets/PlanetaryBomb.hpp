#pragma once

#include "Bullet.hpp"

class PlanetaryBomb : public Bullet {
public:
    PlanetaryBomb(Vector2f pos, int level,Vector2f direction = Vector2f(1.f, 0.f),
                float initialVelocity = 2.f, float maxVelocity = 50.f,
                float acceleration = 1.f);
    
    void Update(const float &dt) override;
};
