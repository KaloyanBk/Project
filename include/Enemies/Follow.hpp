/**
 * @file Follow.hpp
 * @author Kaloyan
 * @brief This is the header file for the FollowEnemy class, child of Enemy, which is used to create enemies that follow the player.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include "./Enemy.hpp"

class FollowEnemy : public Enemy
{
private:
    float followTimer;
    float followTimerMax;
    bool following = true;
    Vector2f initialDirection;
    float initialDistance;
public:
    FollowEnemy(Texture *texture, Vector2u windowBounds,
                Vector2f position, Vector2f direction,
                Vector2f scale, float exp,
                int hpMax, int damageMax, int damageMin, int playerToFollow = 0);
    virtual ~FollowEnemy();

    void Move(float dt,  Vector2f playerPosition) override;


};