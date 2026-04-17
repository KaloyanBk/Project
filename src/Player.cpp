/**
 * @file Player.cpp
 * @brief Implementation file for the Player class.
 * @author Kaloyan
 * @version 0.1
 * @date 2024-05-30
 *
 * This file defines the member functions of the Player class, which is used to create player objects.
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "../include/Player.hpp"

unsigned Player::players = 0;
/**
 * @brief Constructs a Player object.
 *
 * @param textures Reference to a DynamicArray of textures.
 * @param windowBounds The bounds of the game window.
 * @param typeOfBullet The type of bullet the player uses.
 * @param UP The keycode for moving up.
 * @param DOWN The keycode for moving down.
 * @param LEFT The keycode for moving left.
 * @param RIGHT The keycode for moving right.
 * @param FIRE The keycode for firing.
 * @param playerLevel The player's level.
 * @param playerExp The player's experience points.
 * @param playerExpNext The experience points needed for the next level.
 * @param playerHp The player's health points.
 * @param playerHpMax The maximum health points of the player.
 * @param playerScore The player's score.
 * @param upperWeaponLevel The level of the upper weapon.
 * @param lowerWeaponLevel The level of the lower weapon.
 * @param upperWeapon Flag indicating whether the upper weapon is equipped.
 * @param lowerWeapon Flag indicating whether the lower weapon is equipped.
 */
Player::Player(DynamicArray<Texture> &textures, Vector2u windowBounds, int typeOfBullet,
               int UP, int DOWN, int LEFT, int RIGHT, int FIRE,
               int playerLevel, float playerExp, float playerExpNext, int playerHp, int playerHpMax, int playerScore,
               int upperWeaponLevel, int lowerWeaponLevel,
               bool uperWeapon, bool lowerWeapon)
    : windowBounds(windowBounds), level(playerLevel), maxLevel(4), exp(playerExp),
      hp(playerHp), hpMax(playerHpMax),
      upperWeaponLevel(upperWeaponLevel), lowerWeaponLevel(lowerWeaponLevel),
      uperWeapon(uperWeapon), lowerWeapon(lowerWeapon),
      damage(1), damageMax(2),
      statPoints(0), upgrade(0),
      endurance(0), armor(0), strength(0), agility(0),
      maxVelocity(25.f), acceleration(0.8f), drag(0.4f),
      score(playerScore), currentWeapon(typeOfBullet)
{
    /// Delta time multiplier
    this->dtMultiplier = 60.f;

    /// Stats
    this->expNext = static_cast<int>((50 / 3) *
                                     (pow((this->level + 1), 3) -
                                      6 * pow((this->level + 1), 2) +
                                      17 * (this->level + 1) - 11));

    /// Set up the sprite

    this->sprite.setTexture(textures[PLAYER]);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setScale(0.1f, 0.1f);
    this->sprite.setPosition(100.f, 100.f);

    this->fireRateMax = 25.f;
    this->fireRate = this->fireRateMax;

    this->damageTimerMax = 5.f;
    this->damageTimer = 0.f;

    /// Controls
    this->controls[controls::UP] = UP;
    this->controls[controls::DOWN] = DOWN;
    this->controls[controls::LEFT] = LEFT;
    this->controls[controls::RIGHT] = RIGHT;
    this->controls[controls::FIRE] = FIRE;

    /// Player number
    Player::players++;
    this->playerNumber = Player::players;
}

/**
 * @brief Destructor for Player.
 */
Player::~Player()
{
    for (size_t i = 0; i < weapons.size(); ++i)
    {
        delete weapons[i];
    }
}

/**
 * @brief Moves the player based on input and physics.
 *
 * @param dt The change in time since the last update.
 */
void Player::Move(const float &dt)
{
    /// Update velocity
    if (this->inputUp)
    {
        this->direction = Vector2f(0.f, -1.f);
        if (this->currentVelocity.y > -this->maxVelocity && this->direction.y < 0)
            this->currentVelocity.y += this->direction.y * this->acceleration * dt * this->dtMultiplier;
    }
    else if (this->inputDown)
    {
        this->direction = Vector2f(0.f, 1.f);
        if (this->currentVelocity.y < this->maxVelocity && this->direction.y > 0)
            this->currentVelocity.y += this->direction.y * this->acceleration * dt * this->dtMultiplier;
    }
    if (this->inputLeft)
    {
        this->direction = Vector2f(-1.f, 0.f);
        if (this->currentVelocity.x < this->maxVelocity && this->direction.x < 0)
            this->currentVelocity.x += this->direction.x * this->acceleration * dt * this->dtMultiplier;
    }
    else if (this->inputRight)
    {
        this->direction = Vector2f(1.f, 0.f);
        if (this->currentVelocity.x < this->maxVelocity && this->direction.x > 0)
            this->currentVelocity.x += this->direction.x * this->acceleration * dt * this->dtMultiplier;
    }
    /// Drag
    if (this->currentVelocity.x > 0)
    {
        this->currentVelocity.x -= this->drag * dt * this->dtMultiplier;
        if (this->currentVelocity.x < 0)
            this->currentVelocity.x = 0;
    }
    else if (this->currentVelocity.x < 0)
    {
        this->currentVelocity.x += this->drag * dt * this->dtMultiplier;
        if (this->currentVelocity.x > 0)
            this->currentVelocity.x = 0;
    }
    if (this->currentVelocity.y > 0)
    {
        this->currentVelocity.y -= this->drag * dt * this->dtMultiplier;
        if (this->currentVelocity.y < 0)
            this->currentVelocity.y = 0;
    }
    else if (this->currentVelocity.y < 0)
    {
        this->currentVelocity.y += this->drag * dt * this->dtMultiplier;
        if (this->currentVelocity.y > 0)
            this->currentVelocity.y = 0;
    }
    this->sprite.move(this->currentVelocity.x * dt * this->dtMultiplier, this->currentVelocity.y * dt * this->dtMultiplier);

    /// Wall collision
    if (this->sprite.getPosition().x - this->sprite.getGlobalBounds().width / 2.f < 0)
        this->sprite.setPosition(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getPosition().y);
    else if (this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2.f > this->windowBounds.x)
        this->sprite.setPosition(this->windowBounds.x - this->sprite.getGlobalBounds().width / 2.f, this->sprite.getPosition().y);
    if (this->sprite.getPosition().y - this->sprite.getGlobalBounds().height / 2.f < 0)
        this->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getGlobalBounds().height / 2.f);
    else if (this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2.f > this->windowBounds.y)
        this->sprite.setPosition(this->sprite.getPosition().x, this->windowBounds.y - this->sprite.getGlobalBounds().height / 2.f);
}

/**
 * @brief Retrieves a bullet by index.
 *
 * @param index The index of the bullet.
 * @return Reference to the bullet.
 * @throws An exception if index is out of bounds.
 */
Bullet &Player::getBullet(unsigned index)
{
    if (index < 0 || index >= this->bullets.size())
    {
        throw "OUT OF BOUNDS! PLAYER::GETBULLET!";
    }
    return *this->bullets[index];
}

/**
 * @brief Removes a bullet from the player's inventory.
 *
 * @param index The index of the bullet to remove.
 * @throws An exception if index is out of bounds.
 */
void Player::removeBullet(unsigned index)
{
    if (index < 0 || index >= this->bullets.size())
    {
        throw "OUT OF BOUNDS! PLAYER::REMOVEBULLET!";
    }
    this->bullets.remove(index);
}

/**
 * @brief Levels up the player.
 */
void Player::LevelUp()
{
    this->statPoints++;
    this->exp -= this->expNext;
    this->expNext = static_cast<int>((50 / 3) *
                                     (pow((this->level + 1), 3) -
                                      6 * pow((this->level + 1), 2) +
                                      17 * (this->level + 1) - 12));

    this->hpMax = static_cast<int>(10 * pow(1.1, (this->level + 1)));
    this->hp = this->hpMax;
}

/**
 * @brief Updates the player's leveling system.
 *
 * @return True if player leveled up, false otherwise.
 */
bool Player::updateLevelingSystem()
{
    if (this->exp >= this->expNext)
    {
        this->level++;
        if (this->level < this->maxLevel)
        {
            LevelUp();
        }
        else
        {
            LevelUp();
            this->exp = this->expNext;
            this->isAtMaxLevel = true;
        }
        return true;
    }
    return false;
}

/**
 * @brief Adds a weapon to the player's inventory.
 *
 * @param type The type of weapon to add.
 * @param UpOrDown Specifies upper or lower weapon.
 * @param level The level of the weapon.
 */
void Player::addWeapon(int type, int UpOrDown, int level)
{
    switch (type)
    {
    case PEA_SHOOTER:

        sideGunUp = new PeaShooter(level, UpOrDown);
        weapons.add(sideGunUp);

        break;
    }
}

/**
 * @brief Updates the accessories (weapons) of the player.
 *
 * @param dt The change in time since the last update.
 */
void Player::UpdateAccessories(const float &dt)
{
    for (size_t i = 0; i < weapons.size(); ++i)
    {
        weapons[i]->Update(this->sprite.getPosition(), getBounds(), dt);
    }
}

/**
 * @brief Sets the type of bullet fired by the player.
 *
 * @tparam T The type of bullet.
 * @param pos The position from which the bullet is fired.
 * @param upgrade The upgrade level of the bullet.
 * @param level The level of the player.
 * @param directionUp The direction vector for upper bullet.
 * @param directionDown The direction vector for lower bullet.
 * @param initialVelocity The initial velocity of the bullet.
 * @param maxVelocity The maximum velocity of the bullet.
 * @param acceleration The acceleration of the bullet.
 */
template <typename T>
void Player::setBulletType(Vector2f pos, int upgrade, int level, Vector2f directionUp, Vector2f directionDown,
                           float initialVelocity, float maxVelocity, float acceleration)
{
    switch (upgrade)
    {
    case 0:
        this->bullets.add(new T(pos, this->level));
        break;

    case 1:
        this->bullets.add(new T(pos, this->level, directionUp, initialVelocity, maxVelocity, acceleration));
        this->bullets.add(new T(pos, this->level, directionDown, initialVelocity, maxVelocity, acceleration));
        break;
    case 2:
        this->bullets.add(new T(pos, this->level, directionUp, initialVelocity, maxVelocity, acceleration));
        this->bullets.add(new T(pos, this->level));
        this->bullets.add(new T(pos, this->level, directionDown, initialVelocity, maxVelocity, acceleration));
        break;
    }
}

/**
 * @brief Updates combat-related actions of the player.
 */
void Player::CombatUpdate()

{

    /// change main gun level with number keys

    if (Keyboard::isKeyPressed(Keyboard::P))
    {
        this->upgrade = 0;
    }
    else if (Keyboard::isKeyPressed(Keyboard::O))
    {
        this->upgrade = 1;
    }
    else if (Keyboard::isKeyPressed(Keyboard::I))
    {
        this->upgrade = 2;
    }

    Vector2f bulletPosition = this->sprite.getPosition() + Vector2f(30.f, 0.f);
    /// Fire main gun

    switch (this->currentWeapon)
    {
    case LASER:
        this->setBulletType<LaserBullet>(bulletPosition, this->upgrade, this->level);
        break;
    case LIGHTNING:
        this->setBulletType<Lightning>(bulletPosition, this->upgrade, this->level);
        break;
    case DARK_MATTER:
        this->setBulletType<DarkMatter>(bulletPosition, this->upgrade, this->level);
        break;
    case NUCLIER_MATERIAL:
        this->setBulletType<NuclierMaterial>(bulletPosition, this->upgrade, this->level);
        break;
    case PLASMA:
        this->setBulletType<Plasma>(bulletPosition, this->upgrade, this->level);
        break;
    case PLANETARY_BOMB:
        this->setBulletType<PlanetaryBomb>(bulletPosition, this->upgrade, this->level);
        break;
    }

    this->fireRate = 0;

    /// Fire side guns
    for (size_t i = 0; i < weapons.size(); ++i)
    {
        weapons[i]->Fire(weapons[i]->getPosition(), Vector2f(1.f, 0.f), Vector2f(0.2f, 0.2f));
    }
}

/**
 * @brief Inflicts damage on the player.
 *
 * @param damage The amount of damage to inflict.
 */
void Player::TakeDamage(int damage)
{
    if (this->damageTimer >= this->damageTimerMax)
    {
        this->hp -= damage;
        this->damageTimer = 0;
    }
    if (this->hp <= 0)
        this->hp = 0;
}

/**
 * @brief Updates the player's state.
 *
 * @param windowBounds The bounds of the game window.
 * @param dt The change in time since the last update.
 */
void Player::Update(Vector2u windowBounds, const float &dt)
{

    if (uperWeapon && !this->addedUpperWeapon)
    {
        this->addWeapon(PEA_SHOOTER, WEAPON_UP, this->upperWeaponLevel);
        this->addedUpperWeapon = true;
    }
    if (lowerWeapon && !this->addedLowerWeapon)
    {
        this->addWeapon(PEA_SHOOTER, WEAPON_DOWN, this->lowerWeaponLevel);
        this->addedLowerWeapon = true;
    }
    /// Update fire rate
    if (this->fireRate < this->fireRateMax)
        this->fireRate += 1.f * dt * this->dtMultiplier;
    if (this->damageTimer < this->damageTimerMax)
        this->damageTimer += 1.f * dt * this->dtMultiplier;

    /// Update weapons and bullets
    for (size_t i = 0; i < weapons.size(); ++i)
    {
        for (size_t j = 0; j < weapons[i]->getBullets().size(); ++j)
        {
            weapons[i]->getBullets()[j]->Update(dt);
            /// Remove bullets that have gone off-screen
            if (weapons[i]->getBullets()[j]->getPosition().x > windowBounds.x)
            {
                delete weapons[i]->getBullets()[j];
                weapons[i]->getBullets().erase(weapons[i]->getBullets().begin() + j);
                /// Decrement j to account for the erased element
                --j;
            }
        }
    }

    /// Update player movement and accessories
    this->Move(dt);
    this->UpdateAccessories(dt);

    /// Check for firing input and perform combat update
    if (this->inputFire && this->fireRate >= this->fireRateMax)
    {
        this->CombatUpdate();
    }
}

/**
 * @brief Renders the player and associated elements.
 *
 * @param target The render target.
 */
void Player::Render(RenderTarget &target)
{
    /// Render bullets
    for (size_t i = 0; i < this->bullets.size(); i++)
        this->bullets[i]->Render(target);

    /// Render weapons
    for (size_t i = 0; i < this->weapons.size(); i++)
        this->weapons[i]->Render(target);

    /// Render the player
    target.draw(this->sprite);
}
