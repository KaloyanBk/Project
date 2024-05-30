/**
 * @file Weapon.hpp
 * @author Kaloyan
 * @brief This is the header file for the Weapon class, which is used to create weapons for the player to shoot.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include "../Bullets/Bullet.hpp"
#include "../Resources/Textures.hpp"

class Weapon
{
protected:
    float dtMultiplier;

    int fireRate;
    int fireRateMax;
    Sprite sprite;
    Texture* weaponTexture;
    std::vector<Bullet *> bullets;

    int bulletLevel;
    int damage;
    int damageMax;
    int UpOrDown;
    int level;

public:
    // Constructor
    Weapon();
    Weapon(int type, int level, int UpOrDown,int fireRateMax = 25, int damageMax = 1);
    virtual ~Weapon();

    // Accessors
    inline std::vector<Bullet*>& getBullets() { return bullets; }
    const Vector2f& getPosition() const { return sprite.getPosition(); }
    const FloatRect getBounds() const { return sprite.getGlobalBounds(); }

    // Setters
    void setPosition(const Vector2f& position) { sprite.setPosition(position); }

    // Virtual functions
    virtual void Update(Vector2f targetPosition, FloatRect bounds, const float &dt);
    virtual void Fire(const Vector2f& position, const Vector2f& direction, const Vector2f& scale);
    virtual void Upgrade();

    // Functions
    void Render(RenderTarget& target);
};
