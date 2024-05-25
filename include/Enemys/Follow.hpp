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

    // Override functions
    void Move(float dt,  Vector2f playerPosition) override;


};