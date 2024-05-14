#pragma once

#include "Bullet.hpp"
#include "../include/Weapons/Weapon.hpp"
#include "../include/Weapons/PeaShooter.hpp"
#include "./Resources/Fonts.hpp"
#include "./Resources/Textures.hpp"

class Player {
private:
    unsigned playerNumber;

    // Player sprite
    Sprite sprite;
    RectangleShape hitbox;

    Vector2u windowBounds;

    // Bullets
    std::vector<Bullet> bullets;

    // Controls
    int controls[5];
    Vector2f direction;
    Vector2f currentVelocity;
    float maxVelocity;
    float acceleration;
    float drag;

    // Player stats
    int fireRate;
    int fireRateMax;
    int damageTimer;
    int damageTimerMax;
    int level;
    int exp;
    int expNext;
    int hp;
    int hpMax;
    int damage;
    int damageMax;
    int score;

    // Weapons
    std::vector<Weapon*> weapons;
    Weapon* sideGunUp;
    Weapon* sideGunDown;

    // Main gun
    Texture* laserBullet;
    Texture* lightningBullet;
    Texture* darkMatterBullet;
    Texture* nuclierMaterialBullet;
    Texture* plasmaBullet;
    Texture* planetaryBombBullet;

    int currentWeapon;

    // Upgarde system
    int mainGunLevel;
    bool dualBullets = false;
    bool tripleBullets = false;
    int sideGunLevel;

public:

    // Constructor
    Player(std::vector<Texture> &textures, Vector2u windowBounds, int UP = 22, int DOWN = 18, int LEFT = 0, int RIGHT = 3, int FIRE = 57);
    ~Player();

    // Accessors
    inline std::vector<Bullet> &getBullets() { return this->bullets; }
    inline const Vector2f &getPosition() const { return this->sprite.getPosition(); }
    inline std::vector<Weapon*> &getWeapons() { return this->weapons; };
    inline const String getHpS() const { return std::to_string(this->hp) + "/" + std::to_string(this->hpMax); }
    inline const FloatRect getBounds() const { return this->sprite.getGlobalBounds(); }
    inline const bool isDead() const { return this->hp <= 0; }

    // Functions
    void Move();
    void addWeapon(Texture* weaponTexture, Texture* bulletTexture, int UpOrDown);
    void CombatUpdate();
    void UpdateAccessories();
    void TakeDamage(int damage);
    void Update(Vector2u windowBounds);
    void Render(RenderTarget &target);

    static unsigned players;
};

// Enumerations
enum controls {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    FIRE
};
enum mainWeapons {
    LASER=0,
    LIGHTNING,
    DARK_MATTER,
    NUCLIER_MATERIAL,
    PLASMA,
    PLANETARY_BOMB
};

enum sideWeapons {
    WEAPON_DOWN = 0,
    WEAPON_UP
};
