/**
 * @file DarkMatter.hpp
 * @author Kaloyan
 * @brief This is the header file for the DarkMatter class, child of Bullet, which is used to create DarkMatter bullets for the player to shoot.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include "Bullet.hpp"

class DarkMatter : public Bullet {
public:
    DarkMatter(Vector2f pos, int level, Vector2f direction = Vector2f(1.f, 0.f), 
                float initialVelocity = 2.f, float maxVelocity = 50.f,
                float acceleration = 1.f);
    
    void Update(const float &dt) override;
};
