#pragma once

#include "../Bullets/Bullet.hpp"
#include "../Resources/Fonts.hpp"
#include "../Resources/Textures.hpp"

class Enemy
{
protected:
    float dtMultiplier;
    Sprite sprite;
    Texture *texture;
    Vector2f direction;
    Vector2u windowBounds;

    int type;
    int hp;
    int hpMax;
    int damageMin;
    int damageMax;

public:
    Enemy(Texture *texture, Vector2u windowBounds,
          Vector2f position, Vector2f direction,
          Vector2f scale, int type,
          int hpMax, int damageMax, int damageMin);
    virtual ~Enemy();

    // Accessors
    inline const int getdamage() const { return rand() % this->damageMax + this->damageMin; }
    inline const int getHp() const { return this->hp; }
    inline const int getHpMax() const { return this->hpMax; }
    inline const bool isDead() const { return this->hp <= 0; }

    inline const FloatRect getBounds() const { return this->sprite.getGlobalBounds(); }
    inline const Vector2f &getPosition() const { return this->sprite.getPosition(); }

    // Functions
    void TakeDamage(int damage);
    virtual void Move(const float &dt);
    virtual void Update(const float &dt);
    void Render(RenderTarget &target);
};

enum enemyTypes
{
    MOVE_LEFT = 0,
    FOLLOW,
    FOLLOW_FAST,
    FOLLOW_SHOOT,
};