#include "../include/Player.hpp"

unsigned Player::players = 0;

Player::Player(std::vector<Texture> &textures, Vector2u windowBounds,
               int UP, int DOWN, int LEFT, int RIGHT, int FIRE)
    : windowBounds(windowBounds), level(0), maxLevel(4), exp(0),
      hp(10), hpMax(10),
      damage(1), damageMax(2),
      statPoints(0), upgrade(0),
      endurance(0), armor(0), strength(0), agility(0),
      maxVelocity(25.f), acceleration(0.8f), drag(0.4f),
      score(0)
{
    // Delta time multiplier
    this->dtMultiplier = 60.f;

    // Stats
    this->expNext = static_cast<int>((50 / 3) *
                                     (pow((this->level + 1), 3) -
                                      6 * pow((this->level + 1), 2) +
                                      17 * (this->level + 1) - 11));

    // Set up the sprite
    this->sprite.setTexture(textures[PLAYER]);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setScale(0.1f, 0.1f);
    this->sprite.setPosition(100.f, 100.f);

    this->fireRateMax = 25.f;
    this->fireRate = this->fireRateMax;
    this->damageTimerMax = 10.f;
    this->damageTimer = this->damageTimerMax;

    // Weapons
    // this->currentWeapon = LASER;
    // this->currentWeapon = LIGHTNING;
    // this->currentWeapon = DARK_MATTER;
    // this->currentWeapon = NUCLIER_MATERIAL;
    // this->currentWeapon = PLASMA;
    this->currentWeapon = PLANETARY_BOMB;

    this->mainGunLevel = 0;

    this->addWeapon(&textures[SIDE_GUN_UP], WEAPON_UP);
    this->addWeapon(&textures[SIDE_GUN_DOWN], WEAPON_DOWN);

    // Controls
    this->controls[controls::UP] = UP;
    this->controls[controls::DOWN] = DOWN;
    this->controls[controls::LEFT] = LEFT;
    this->controls[controls::RIGHT] = RIGHT;
    this->controls[controls::FIRE] = FIRE;

    // Player number
    Player::players++;
    this->playerNumber = Player::players;
}

Player::~Player()
{
    for (auto &w : weapons)
        delete w;
}

void Player::Move(const float &dt)
{
    // Update velocity
    if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::UP])))
    {
        this->direction = Vector2f(0.f, -1.f);
        if (this->currentVelocity.y > -this->maxVelocity && this->direction.y < 0)
            this->currentVelocity.y += this->direction.y * this->acceleration * dt * this->dtMultiplier;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::DOWN])))
    {
        this->direction = Vector2f(0.f, 1.f);
        if (this->currentVelocity.y < this->maxVelocity && this->direction.y > 0)
            this->currentVelocity.y += this->direction.y * this->acceleration * dt * this->dtMultiplier;
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::LEFT])))
    {
        this->direction = Vector2f(-1.f, 0.f);
        if (this->currentVelocity.x < this->maxVelocity && this->direction.x < 0)
            this->currentVelocity.x += this->direction.x * this->acceleration * dt * this->dtMultiplier;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::RIGHT])))
    {
        this->direction = Vector2f(1.f, 0.f);
        if (this->currentVelocity.x < this->maxVelocity && this->direction.x > 0)
            this->currentVelocity.x += this->direction.x * this->acceleration * dt * this->dtMultiplier;
    }
    // Drag
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

    // Wall collision
    if (this->sprite.getPosition().x - this->sprite.getGlobalBounds().width / 2.f < 0)
        this->sprite.setPosition(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getPosition().y);
    else if (this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2.f > this->windowBounds.x)
        this->sprite.setPosition(this->windowBounds.x - this->sprite.getGlobalBounds().width / 2.f, this->sprite.getPosition().y);
    if (this->sprite.getPosition().y - this->sprite.getGlobalBounds().height / 2.f < 0)
        this->sprite.setPosition(this->sprite.getPosition().x, this->sprite.getGlobalBounds().height / 2.f);
    else if (this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2.f > this->windowBounds.y)
        this->sprite.setPosition(this->sprite.getPosition().x, this->windowBounds.y - this->sprite.getGlobalBounds().height / 2.f);
}
void Player::LevelUp()
{
    this->statPoints++;
    this->exp -= this->expNext;
    this->expNext = static_cast<int>((50 / 3) *
                                     (pow((this->level + 1), 3) -
                                      6 * pow((this->level + 1), 2) +
                                      17 * (this->level + 1) - 12));

    // this->hpMax = static_cast<int>(10 * pow(1.1, (this->level + 1)));
    this->hp = this->hpMax;
}

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

void Player::addWeapon(Texture *weaponTexture, int UpOrDown)
{
    if (UpOrDown == WEAPON_UP)
    {
        sideGunUp = new PeaShooter(weaponTexture, this->level, UpOrDown);
        weapons.push_back(sideGunUp);
    }
    else
    {
        sideGunDown = new PeaShooter(weaponTexture, this->level, UpOrDown);
        weapons.push_back(sideGunDown);
    }
}

void Player::UpdateAccessories(const float &dt)
{
    for (auto &w : weapons)
        w->Update(this->sprite.getPosition(), getBounds(), dt);
}

template <typename T>
void Player::setBulletType(Vector2f pos, int upgrade, int level, Vector2f directionUp, Vector2f directionDown,
                           float initialVelocity, float maxVelocity, float acceleration)
{
    switch (upgrade)
    {
    case 0:
        this->bullets.push_back(new T(pos, this->level));
        break;

    case 1:
        this->bullets.push_back(new T(pos, this->level, directionUp, initialVelocity, maxVelocity, acceleration));
        this->bullets.push_back(new T(pos, this->level, directionDown, initialVelocity, maxVelocity, acceleration));
        break;
    case 2:
        this->bullets.push_back(new T(pos, this->level, directionUp, initialVelocity, maxVelocity, acceleration));
        this->bullets.push_back(new T(pos, this->level));
        this->bullets.push_back(new T(pos, this->level, directionDown, initialVelocity, maxVelocity, acceleration));
        break;
    }
}

void Player::CombatUpdate()

{
    // change main gun level with number keys

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
    // Fire main gun
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

    // Fire side guns
    for (auto &w : weapons)
    {
        w->Fire(w->getPosition(), Vector2f(1.f, 0.f), Vector2f(0.2f, 0.2f));
    }
}

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

void Player::Update(Vector2u windowBounds, const float &dt)
{

    // Update fire rate
    if (this->fireRate < this->fireRateMax)
        this->fireRate += 1.f * dt * this->dtMultiplier;
    if (this->damageTimer < this->damageTimerMax)
        this->damageTimer += 1.f * dt * this->dtMultiplier;

    // Update weapons
    for (auto &w : weapons)
    {
        for (size_t i = 0; i < w->getBullets().size(); i++)
        {
            w->getBullets()[i]->Update(dt);
            if (w->getBullets()[i]->getPosition().x > windowBounds.x)
            {
                delete w->getBullets()[i];
                w->getBullets().erase(w->getBullets().begin() + i);
                return;
            }
        }
    }
    this->Move(dt);
    this->UpdateAccessories(dt);
    if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::FIRE])) && this->fireRate >= this->fireRateMax)
    {
        this->CombatUpdate();
    }
}

void Player::Render(RenderTarget &target)
{
    // Render bullets
    for (size_t i = 0; i < this->bullets.size(); i++)
        this->bullets[i]->Render(target);

    // Render weapons
    for (size_t i = 0; i < this->weapons.size(); i++)
        this->weapons[i]->Render(target);

    // Render the player
    target.draw(this->sprite);
}
