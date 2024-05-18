#pragma once

#include "../Bullets/Bullet.hpp"

class Weapon
{
protected:
    float dtMultiplier;

    int fireRate;
    int fireRateMax;
    Sprite sprite;
    Texture* weaponTexture;
    std::vector<Bullet *> bullets;

    int level;
    int damage;
    int damageMax;
    int UpOrDown;

public:
    // Constructor
    Weapon();
    Weapon(Texture* weaponTexture, int UpOrDown, int fireRateMax = 25, int damageMax = 1);
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
