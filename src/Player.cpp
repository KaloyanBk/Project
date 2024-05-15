#include "../include/Player.hpp"

unsigned Player::players = 0;

Player::Player(std::vector<Texture> &textures, Vector2u windowBounds, int UP, int DOWN, int LEFT, int RIGHT, int FIRE)
    : windowBounds(windowBounds), level(1), exp(0), expNext(100), hp(10), hpMax(10), damage(1), damageMax(2),
      score(0), maxVelocity(25.f), acceleration(0.8f), drag(0.4f)
{
    // Set up the sprite
    this->sprite.setTexture(textures[PLAYER]);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);
    this->sprite.setScale(0.1f, 0.1f);
    this->sprite.setPosition(100.f, 100.f);

    this->fireRateMax = 25;
    this->fireRate = this->fireRateMax;
    this->damageTimerMax = 10;
    this->damageTimer = this->damageTimerMax;

    // Weapons
    // this->currentWeapon = LASER;
    // this->currentWeapon = LIGHTNING;
    // this->currentWeapon = DARK_MATTER;
    // this->currentWeapon = NUCLIER_MATERIAL;
    // this->currentWeapon = PLASMA;
    this->currentWeapon = PLANETARY_BOMB;

    this->mainGunLevel = 2;

    this->addWeapon(&textures[SIDE_GUN_UP], WEAPON_UP);
    this->addWeapon(&textures[SIDE_GUN_DOWN], WEAPON_DOWN);

    // Controls
    this->controls[controls::UP] = UP;
    this->controls[controls::DOWN] = DOWN;
    this->controls[controls::LEFT] = LEFT;
    this->controls[controls::RIGHT] = RIGHT;
    this->controls[controls::FIRE] = FIRE;

    // Player number
    this->playerNumber = Player::players;
    Player::players++;
}

Player::~Player()
{
    for (auto &w : weapons)
        delete w;
}

void Player::Move()
{
    // Update velocity
    if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::UP])))
    {
        this->direction = Vector2f(0.f, -1.f);
        if (this->currentVelocity.y > -this->maxVelocity && this->direction.y < 0)
            this->currentVelocity.y += this->direction.y * this->acceleration;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::DOWN])))
    {
        this->direction = Vector2f(0.f, 1.f);
        if (this->currentVelocity.y < this->maxVelocity && this->direction.y > 0)
            this->currentVelocity.y += this->direction.y * this->acceleration;
    }
    if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::LEFT])))
    {
        this->direction = Vector2f(-1.f, 0.f);
        if (this->currentVelocity.x < this->maxVelocity && this->direction.x < 0)
            this->currentVelocity.x += this->direction.x * this->acceleration;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key(this->controls[controls::RIGHT])))
    {
        this->direction = Vector2f(1.f, 0.f);
        if (this->currentVelocity.x < this->maxVelocity && this->direction.x > 0)
            this->currentVelocity.x += this->direction.x * this->acceleration;
    }
    // Drag
    if (this->currentVelocity.x > 0)
    {
        this->currentVelocity.x -= this->drag;
        if (this->currentVelocity.x < 0)
            this->currentVelocity.x = 0;
    }
    else if (this->currentVelocity.x < 0)
    {
        this->currentVelocity.x += this->drag;
        if (this->currentVelocity.x > 0)
            this->currentVelocity.x = 0;
    }
    if (this->currentVelocity.y > 0)
    {
        this->currentVelocity.y -= this->drag;
        if (this->currentVelocity.y < 0)
            this->currentVelocity.y = 0;
    }
    else if (this->currentVelocity.y < 0)
    {
        this->currentVelocity.y += this->drag;
        if (this->currentVelocity.y > 0)
            this->currentVelocity.y = 0;
    }
    this->sprite.move(this->currentVelocity);

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
void Player::addWeapon(Texture *weaponTexture, int UpOrDown)
{
    if (UpOrDown == 0)
    {
        sideGunUp = new PeaShooter(weaponTexture, UpOrDown);
        weapons.push_back(sideGunUp);
    }
    else
    {
        sideGunDown = new PeaShooter(weaponTexture, UpOrDown);
        weapons.push_back(sideGunDown);
    }
}

void Player::UpdateAccessories()
{
    for (auto &w : weapons)
        w->Update(this->sprite.getPosition(), getBounds());
}

void Player::CombatUpdate()

{
    Vector2f bulletPosition = this->sprite.getPosition() + Vector2f(30.f, 0.f);
    // Fire main gun
    if (this->currentWeapon == LASER)
    {
        if (!this->dualBullets && !this->tripleBullets)
        {
            this->bullets.push_back(new LaserBullet(bulletPosition));
        }
        else if (this->dualBullets && !this->tripleBullets)
        {
            this->bullets.push_back(
                new LaserBullet(bulletPosition + Vector2f(0.f, 10.f), Vector2f(1.f, 0.1f)));

            this->bullets.push_back(
                new LaserBullet(bulletPosition - Vector2f(0.f, 10.f), Vector2f(1.f, -0.1f)));
        }
        else if (!this->dualBullets && this->tripleBullets)
        {
            this->bullets.push_back(
                new LaserBullet(bulletPosition + Vector2f(0.f, 10.f), Vector2f(1.f, 0.1f)));

            this->bullets.push_back(
                new LaserBullet(bulletPosition));

            this->bullets.push_back(
                new LaserBullet(bulletPosition - Vector2f(0.f, 10.f), Vector2f(1.f, -0.1f)));
        }
    }
    else if (this->currentWeapon == LIGHTNING)
    {
        if (!this->dualBullets && !this->tripleBullets)
        {
            this->bullets.push_back(new Lightning(bulletPosition));
        }
        else if (this->dualBullets && !this->tripleBullets)
        {
            this->bullets.push_back(
                new Lightning(bulletPosition + Vector2f(0.f, 10.f), Vector2f(1.f, 0.1f)));

            this->bullets.push_back(
                new Lightning(bulletPosition - Vector2f(0.f, 10.f), Vector2f(1.f, -0.1f)));
        }
        else if (!this->dualBullets && this->tripleBullets)
        {
            this->bullets.push_back(
                new Lightning(bulletPosition + Vector2f(0.f, 10.f), Vector2f(1.f, 0.1f)));

            this->bullets.push_back(
                new Lightning(bulletPosition));

            this->bullets.push_back(
                new Lightning(bulletPosition - Vector2f(0.f, 10.f), Vector2f(1.f, -0.1f)));
        }
    }
    else if (this->currentWeapon == DARK_MATTER)
    {
        if (!this->dualBullets && !this->tripleBullets)
        {
            this->bullets.push_back(new DarkMatter(bulletPosition));
        }
        else if (this->dualBullets && !this->tripleBullets)
        {
            this->bullets.push_back(
                new DarkMatter(bulletPosition + Vector2f(0.f, 10.f), Vector2f(1.f, 0.1f)));

            this->bullets.push_back(
                new DarkMatter(bulletPosition - Vector2f(0.f, 10.f), Vector2f(1.f, -0.1f)));
        }
        else if (!this->dualBullets && this->tripleBullets)
        {
            this->bullets.push_back(
                new DarkMatter(bulletPosition + Vector2f(0.f, 10.f), Vector2f(1.f, 0.1f)));

            this->bullets.push_back(
                new DarkMatter(bulletPosition));

            this->bullets.push_back(
                new DarkMatter(bulletPosition - Vector2f(0.f, 10.f), Vector2f(1.f, -0.1f)));
        }
    }
    else if (this->currentWeapon == NUCLIER_MATERIAL)
    {
        if (!this->dualBullets && !this->tripleBullets)
        {
            this->bullets.push_back(new NuclierMaterial(bulletPosition));
        }
        else if (this->dualBullets && !this->tripleBullets)
        {
            this->bullets.push_back(
                new NuclierMaterial(bulletPosition + Vector2f(0.f, 10.f), Vector2f(1.f, 0.1f)));

            this->bullets.push_back(
                new NuclierMaterial(bulletPosition - Vector2f(0.f, 10.f), Vector2f(1.f, -0.1f)));
        }
        else if (!this->dualBullets && this->tripleBullets)
        {
            this->bullets.push_back(
                new NuclierMaterial(bulletPosition + Vector2f(0.f, 10.f), Vector2f(1.f, 0.1f)));

            this->bullets.push_back(
                new NuclierMaterial(bulletPosition));

            this->bullets.push_back(
                new NuclierMaterial(bulletPosition - Vector2f(0.f, 10.f), Vector2f(1.f, -0.1f)));
        }
    }
    else if (this->currentWeapon == PLASMA)
    {
        if (!this->dualBullets && !this->tripleBullets)
        {
            this->bullets.push_back(new Plasma(bulletPosition));
        }
        else if (this->dualBullets && !this->tripleBullets)
        {
            this->bullets.push_back(
                new Plasma(bulletPosition + Vector2f(0.f, 10.f), Vector2f(1.f, 0.1f)));

            this->bullets.push_back(
                new Plasma(bulletPosition - Vector2f(0.f, 10.f), Vector2f(1.f, -0.1f)));
        }
        else if (!this->dualBullets && this->tripleBullets)
        {
            this->bullets.push_back(
                new Plasma(bulletPosition + Vector2f(0.f, 10.f), Vector2f(1.f, 0.1f)));

            this->bullets.push_back(
                new Plasma(bulletPosition));

            this->bullets.push_back(
                new Plasma(bulletPosition - Vector2f(0.f, 10.f), Vector2f(1.f, -0.1f)));
        }
    }
    else if (this->currentWeapon == PLANETARY_BOMB)
    {
        if (!this->dualBullets && !this->tripleBullets)
        {
            this->bullets.push_back(new PlanetaryBomb(bulletPosition));
        }
        else if (this->dualBullets && !this->tripleBullets)
        {
            this->bullets.push_back(
                new PlanetaryBomb(bulletPosition + Vector2f(0.f, 10.f), Vector2f(1.f, 0.1f)));

            this->bullets.push_back(
                new PlanetaryBomb(bulletPosition - Vector2f(0.f, 10.f), Vector2f(1.f, -0.1f)));
        }
        else if (!this->dualBullets && this->tripleBullets)
        {
            this->bullets.push_back(
                new PlanetaryBomb(bulletPosition + Vector2f(0.f, 10.f), Vector2f(1.f, 0.1f)));

            this->bullets.push_back(
                new PlanetaryBomb(bulletPosition));

            this->bullets.push_back(
                new PlanetaryBomb(bulletPosition - Vector2f(0.f, 10.f), Vector2f(1.f, -0.1f)));
        }
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

void Player::Update(Vector2u windowBounds)
{

    // Create a new bullet
    if (this->mainGunLevel == 0)
    {
        this->dualBullets = false;
        this->tripleBullets = false;
    }
    else if (this->mainGunLevel == 1)
    {
        this->dualBullets = true;
        this->tripleBullets = false;
    }
    else if (this->mainGunLevel == 2)
    {
        this->dualBullets = false;
        this->tripleBullets = true;
    }

    // Update fire rate
    if (this->fireRate < this->fireRateMax)
        this->fireRate++;
    if (this->damageTimer < this->damageTimerMax)
        this->damageTimer++;

    // Update weapons
    for (auto &w : weapons)
    {
        for (size_t i = 0; i < w->getBullets().size(); i++)
        {
            w->getBullets()[i]->Update();
            if (w->getBullets()[i]->getPosition().x > windowBounds.x)
            {
                delete w->getBullets()[i];
                w->getBullets().erase(w->getBullets().begin() + i);
                return;
            }
        }
    }
    this->Move();
    this->UpdateAccessories();
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
