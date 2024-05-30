/**
 * @file MoveLeft.hpp
 * @author Kaloyan
 * @brief This is the header file for the MoveLeftEnemy class, child of Enemy, which is used to create enemies that move left.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include "./Enemy.hpp"

class MoveLeftEnemy : public Enemy
{
private:


public:
    MoveLeftEnemy(Texture *texture, Vector2u windowBounds,
                  Vector2f position, Vector2f direction,
                  Vector2f scale, float exp,
                  int hpMax, int damageMax, int damageMin);
    virtual ~MoveLeftEnemy();

    // Override functions
    void Move(float dt,  Vector2f playerPosition) override;
};
