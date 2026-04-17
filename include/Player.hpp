/**
 * @file Player.hpp
 * @author Kaloyan
 * @brief This is the header file for the Player class, which is used to create the player object.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once
#include <vector>
#include <iostream>

#include "./Bullets/Bullet.hpp"
#include "../include/Weapons/Weapon.hpp"
#include "../include/Weapons/PeaShooter.hpp"
#include "./Resources/Fonts.hpp"
#include "./Resources/Textures.hpp"

#include "../include/Bullets/LaserBullet.hpp"
#include "../include/Bullets/Lightning.hpp"
#include "../include/Bullets/DarkMatter.hpp"
#include "../include/Bullets/NuclierMaterial.hpp"
#include "../include/Bullets/Plasma.hpp"
#include "../include/Bullets/PlanetaryBomb.hpp"

class Player
{
private:
    unsigned playerNumber;
    float dtMultiplier;

    // Player sprite
    Sprite sprite;
    RectangleShape hitbox;

    Vector2u windowBounds;

    // Bullets
    DynamicArray<Bullet *> bullets;

    // Controls
    int controls[5];
    Vector2f direction;
    Vector2f currentVelocity;
    float maxVelocity;
    float acceleration;
    float drag;

    // Player stats
    float fireRate;
    float fireRateMax;

    float damageTimer;
    float damageTimerMax;
    int damage;
    int damageMax;

    int level;
    int maxLevel;
    bool isAtMaxLevel = false;

    float exp;
    float expNext;
    int statPoints;

    int hp;
    int hpMax;

    int score;

    int endurance;
    int armor;
    int strength;
    int agility;
    int upgrade;

    // Weapons
    DynamicArray<Weapon *> weapons;
    Weapon *sideGunUp;
    Weapon *sideGunDown;

    int currentWeapon;

    bool addedUpperWeapon = false;
    bool addedLowerWeapon = false;

    // Upgarde system
    int sideGunLevel = 0;

    bool uperWeapon;
    bool lowerWeapon;
    int upperWeaponLevel;
    int lowerWeaponLevel;
    // Input state (event-driven)
    bool inputUp = false;
    bool inputDown = false;
    bool inputLeft = false;
    bool inputRight = false;
    bool inputFire = false;

public:
    // Constructor
    Player(DynamicArray<Texture> &textures, Vector2u windowBounds, int typeOfBullet,
           int UP = 22, int DOWN = 18, int LEFT = 0, int RIGHT = 3, int FIRE = 57,
           int playerLevel = 0, float playerExp = 0, float playerExpNext = 16, int playerHp = 10, int playerHpMax = 10, int playerScore = 0,
           int upperWeaponLevel = 0, int lowerWeaponLevel = 0,
           bool uperWeapon = false, bool lowerWeapon = false);

    ~Player();

    // Accessors
    Bullet &getBullet(unsigned index);
    void removeBullet(unsigned index);
    inline const int getBulletSize() { return this->bullets.size(); }
    inline const Vector2f &getPosition() const { return this->sprite.getPosition(); }
    inline DynamicArray<Weapon *> &getWeapons() { return this->weapons; };
    inline const String getHpS() const { return std::to_string(this->hp) + "/" + std::to_string(this->hpMax); }
    inline const FloatRect getBounds() const { return this->sprite.getGlobalBounds(); }
    inline const bool isDead() const { return this->hp <= 0; }
    inline const int getPlayerNumber() const { return this->playerNumber; }
    inline const int getLevel() const { return this->level; }
    inline const int getMaxLevel() const { return this->maxLevel; }
    inline const bool getIsAtMaxLevel() const { return this->isAtMaxLevel; }
    inline const int getExp() const { return this->exp; }
    inline const int getExpNext() const { return this->expNext; }
    inline const int getStatPoints() const { return this->statPoints; }
    inline const int getHp() const { return this->hp; }
    inline const int getHpMax() const { return this->hpMax; }
    inline const int getScore() const { return this->score; }
    inline const int getCurrentWeapon() const { return this->currentWeapon; }
    inline bool gainExp(float exp)
    {
        if (!this->isAtMaxLevel)
        {
            this->exp += exp;
            return this->updateLevelingSystem();
        }
        return false;
    }

    // Templait function adding to bullet vector
    template <typename T>
    void setBulletType(Vector2f pos, int upgrade, int level, Vector2f directionUp = Vector2f(1.f, -0.1f), Vector2f directionDown = Vector2f(1.f, 0.1f),
                       float initialVelocity = 2.f, float maxVelocity = 50.f, float acceleration = 1.f);

    // Modifiers
    void setToDefault();
    void setCurrentWeapon(int weapon) { this->currentWeapon = weapon; }
    void setUpperWeaponLevel(int level) { this->upperWeaponLevel = level; }
    void setLowerWeaponLevel(int level) { this->lowerWeaponLevel = level; }
    void setUperWeapon(bool uperWeapon) { this->uperWeapon = uperWeapon; }
    void setLowerWeapon(bool lowerWeapon) { this->lowerWeapon = lowerWeapon; }

    // Input setters
    void setInput(bool up, bool down, bool left, bool right, bool fire)
    {
        this->inputUp = up;
        this->inputDown = down;
        this->inputLeft = left;
        this->inputRight = right;
        this->inputFire = fire;
    }

    void setLevel(int level) { this->level = level; }
    void setExp(float exp) { this->exp = exp; }
    void setExpNext(float expNext) { this->expNext = expNext; }
    void setStatPoints(int statPoints) { this->statPoints = statPoints; }
    void setHp(int hp) { this->hp = hp; }
    void setHpMax(int hpMax) { this->hpMax = hpMax; }
    void setScore(int score) { this->score = score; }

    // Functionsc
    void Move(const float &dt);
    bool updateLevelingSystem();
    void LevelUp();
    void addWeapon(int type, int UpOrDown, int level);
    void CombatUpdate();
    void UpdateAccessories(const float &dt);
    void TakeDamage(int damage);
    void Update(Vector2u windowBounds, const float &dt);
    void Render(RenderTarget &target);

    static unsigned players;
};

// Enumerations
enum controls
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    FIRE
};
enum mainWeapons
{
    LASER = 0,
    LIGHTNING,
    DARK_MATTER,
    NUCLIER_MATERIAL,
    PLASMA,
    PLANETARY_BOMB
};

enum sideWeapons
{
    WEAPON_UP = 0,
    WEAPON_DOWN
};
