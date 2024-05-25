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
