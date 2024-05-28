#include "../include/Game.hpp"
#include "../include/Weapons/PeaShooter.hpp"
#include <iostream>

// Constructor
Game::Game(RenderWindow *window,
           int numberOfPlayers,
           int player1Level, int player1Hp, int player1HpMax, float player1Exp, float player1ExpNext, int player1Score,
           int player2Level, int player2Hp, int player2HpMax, float player2Exp, float player2ExpNext, int player2Score,
           bool upperWeapon, int upperWeaponLevel,
           bool lowerWeapon, int lowerWeaponLevel)
    : window(window), numberOfPlayers(numberOfPlayers),
      player1Level(player1Level), player2Level(player2Level), upperWeaponLevel(upperWeaponLevel), lowerWeaponLevel(lowerWeaponLevel),
      upperWeapon(upperWeapon), lowerWeapon(lowerWeapon), player1Exp(player1Exp), player2Exp(player2Exp),
      player1ExpNext(player1ExpNext), player1Hp(player1Hp), player1HpMax(player1HpMax), player1Score(player1Score),
      player2ExpNext(player2ExpNext), player2Hp(player2Hp), player2HpMax(player2HpMax), player2Score(player2Score)
{
    // Window settings
    this->dtMultiplier = 60.f;

    // Load resources
    this->loadTextures();

    // Create players
    this->createPlayers();


    // Initialize enemy spawn timer
    this->enemySpawnTimerMax = 25.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;

    // Initialize UI
    this->InItUi();
}

// Destructor
Game::~Game()
{
    for (auto &p : players)
    {
        delete p;
    }

    for (size_t i = 0; i < enemys.size(); ++i)
    {
        delete enemys[i];
    }
    enemys.clear();
}

// Load textures
void Game::loadTextures()
{
    for (size_t i = 0; i < NUM_RESOURCES; ++i)
    {
        Texture texture;

        if (!texture.loadFromFile(resourcePaths.at(static_cast<Textures>(i))))
        {
            std::cerr << "Failed to load texture: " << resourcePaths.at(static_cast<Textures>(i)) << std::endl;
        }
        this->textures.add(texture);
    }
}

// Create players
void Game::createPlayers()
{
    switch (numberOfPlayers)
    {
    case 1:

        this->players.push_back(createPlayer(this->textures, this->window->getSize(),
                                             this->player1Level, this->player1Exp, this->player1ExpNext, this->player1Hp,
                                             this->player1HpMax, this->player1Score,
                                             Keyboard::W, Keyboard::S, Keyboard::A, Keyboard::D, Keyboard::Space));
        break;
    case 2:
        this->players.push_back(createPlayer(this->textures, this->window->getSize(),
                                             this->player1Level, this->player1Exp, this->player1ExpNext, this->player1Hp,
                                             this->player1HpMax, this->player1Score,
                                             Keyboard::W, Keyboard::S, Keyboard::A, Keyboard::D, Keyboard::Space));
        this->players.push_back(createPlayer(this->textures, this->window->getSize(),
                                             this->player2Level, this->player2Exp, this->player2ExpNext, this->player2Hp,
                                             this->player2HpMax, this->player2Score, Keyboard::Up, Keyboard::Down, Keyboard::Left, Keyboard::Right, Keyboard::RShift));
        break;
    default:
        break;
    }
}

Player *Game::createPlayer(DynamicArray<Texture> &textures, Vector2u windowBounds,
                           int level, float playerExp, float playerExpNext, int playerHp, int playerHpMax, int playerScore,
                           int upKey, int downKey, int leftKey, int rightKey, int fireKey)
{
    return new Player(textures, windowBounds, upKey, downKey, leftKey, rightKey, fireKey,
                      level, playerExp, playerExpNext, playerHp, playerHpMax, playerScore, this->upperWeaponLevel, this->lowerWeaponLevel, this->upperWeapon,
                      this->lowerWeapon);
}

// Initialize UI elements
void Game::InItUi()
{
    if (!this->font.loadFromFile(resourcePathsFonts.at(DOSIS_LIGHT)))
    {
        std::cerr << "Failed to load font: " << resourcePathsFonts.at(DOSIS_LIGHT) << std::endl;
    }
    this->followPlayerText.setFont(font);
    this->stationaryText.setFont(font);

    // Follow Player Text
    this->followPlayerText.setCharacterSize(22);
    this->followPlayerText.setFillColor(Color::White);

    // Stationary Text
    this->stationaryText.setCharacterSize(12);
    this->stationaryText.setFillColor(Color::White);

    // Player Exp Bar
    this->playerExpBar.setSize(Vector2f(110.f, 12.f));
    this->playerExpBar.setFillColor(Color(0.f, 100.f, 200.f, 200.f));

    // Player Exp Bar Outline
    this->playerExpBarOutline.setSize(Vector2f(110.f, 12.f));
    this->playerExpBarOutline.setFillColor(Color::Transparent);
    this->playerExpBarOutline.setOutlineThickness(1.f);
    this->playerExpBarOutline.setOutlineColor(Color::White);

    // Player Level Text
    this->playerLevelText.setFont(font);
    this->playerLevelText.setCharacterSize(22);
    this->playerLevelText.setFillColor(Color::White);

    // Game Over Text
    if (!this->gameOverFont.loadFromFile(resourcePathsFonts.at(GAME_OVER)))
    {
        std::cerr << "Failed to load font: " << resourcePathsFonts.at(GAME_OVER) << std::endl;
    }
    this->gameOverText.setFont(gameOverFont);
    this->gameOverText.setCharacterSize(60);
    this->gameOverText.setFillColor(Color::White);
    this->gameOverText.setString("Game Over");
    this->gameOverText.setPosition(
        0.f - this->gameOverText.getGlobalBounds().width,
        this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);
}

// Update UI elements for a specific player
void Game::UpdateUI(int index)
{
    if (index >= players.size())
    {
        std::cerr << "Player index out of bounds" << std::endl;
    }
    else
    {
        this->followPlayerText.setPosition(
            this->players[index]->getPosition().x - this->players[index]->getBounds().width / 2.f,
            this->players[index]->getPosition().y - this->players[index]->getBounds().height / 2.f - this->followPlayerText.getGlobalBounds().height - 20.f);

        this->followPlayerText.setString(
            "Player: " + std::to_string(players[index]->getPlayerNumber()) + "\n" +
            "HP: " + players[index]->getHpS());

        this->playerLevelText.setPosition(
            this->players[index]->getPosition().x - this->players[index]->getBounds().width / 2.f + 10.f,
            this->players[index]->getPosition().y + this->players[index]->getBounds().height / 2.f + 30.f);

        if (!this->players[index]->getIsAtMaxLevel())
        {
            this->playerLevelText.setString("Level: " + std::to_string(players[index]->getLevel() + 1));
        }
        else
        {
            this->playerLevelText.setString("Level: MAX");
        }

        // Exp Bar
        this->playerExpBar.setPosition(
            this->players[index]->getPosition().x - this->players[index]->getBounds().width / 2.f + 10.f,
            this->players[index]->getPosition().y + this->players[index]->getBounds().height / 2.f + 10.f);

        this->playerExpBarOutline.setPosition(this->playerExpBar.getPosition());
        this->playerExpBar.setScale(
            static_cast<float>(this->players[index]->getExp()) / static_cast<float>(this->players[index]->getExpNext()), 1.f);
    }
}

// Update game logic
void Game::Update(const float &dt)
{
    if (!gameOver)
    {
        if (enemySpawnTimer < enemySpawnTimerMax)
            enemySpawnTimer += 1.f * dt * this->dtMultiplier;

        // Spawn new enemy
        if (enemySpawnTimer >= enemySpawnTimerMax)
        {
            auto random50_50 = []() -> int
            {
                return rand() % 2;
            };
            // Random chance to spawn a MoveLeftEnemy
            if (rand() % 2 == 0) // 50% chance
            {
                // Randomize properties for MoveLeftEnemy
                float spawnX = static_cast<float>(rand() % static_cast<int>(this->window->getSize().x));
                float spawnY = static_cast<float>(rand() % static_cast<int>(this->window->getSize().y));
                float directionX = -1.f;
                float directionY = 0.f;
                float scale = 0.4f + static_cast<float>((rand() % 20) / 100.0); // Range from 0.5 to 1.0
                int hpMax = rand() % 3 + 1;
                int damageMax = rand() % 5 + 1;
                int damageMin = rand() % 3 + 1;
                float exp = static_cast<float>(rand() % 10 + 1);

                enemys.add(new MoveLeftEnemy(
                    &this->textures[ENEMY_MOVE_LEFT], this->window->getSize(),
                    Vector2f(spawnX, spawnY), Vector2f(directionX, directionY), Vector2f(scale, scale),
                    exp, hpMax, damageMax, damageMin));
            }

            // Random chance to spawn a FollowEnemy
            if (rand() % 2 == 0) // 50% chance
            {
                // Randomize properties for FollowEnemy
                float spawnX = static_cast<float>(rand() % static_cast<int>(this->window->getSize().x));
                float spawnY = static_cast<float>(rand() % static_cast<int>(this->window->getSize().y));
                float directionX = -1.f;
                float directionY = 0.f;
                float scale = 0.4f + static_cast<float>((rand() % 20) / 100.0); // Range from 0.5 to 1.0
                int hpMax = rand() % 3 + 1;
                int damageMax = rand() % 5 + 1;
                int damageMin = rand() % 3 + 1;
                float exp = static_cast<float>(rand() % 10 + 1);

                int playerToFollow = random50_50();

                enemys.add(new FollowEnemy(
                    &this->textures[ENEMY_FOLLOW], this->window->getSize(),
                    Vector2f(spawnX, spawnY), Vector2f(directionX, directionY), Vector2f(scale, scale),
                    exp, hpMax, damageMax, damageMin, playerToFollow));
            }

            // Reset enemy spawn timer
            enemySpawnTimer = 0;

            // Randomize the enemy spawn timer max value to create variable spawn intervals
        }

        // Update players
        for (auto &p : players)
        {
            p->Update(this->window->getSize(), dt);
            this->updateBullets(p, dt);
            this->updateSideGunBullets(p, dt);
        }

        // Update enemies
        for (size_t i = 0; i < enemys.size(); i++)
        {
            int followPlayerIndex = enemys[i]->getPlayerToFollow();
            if (followPlayerIndex >= 0 && followPlayerIndex < players.size())
            {
                enemys[i]->Update(dt, players[followPlayerIndex]->getPosition());
            }
            else
            {
                // Default behavior if player to follow is invalid
                enemys[i]->Update(dt, players[0]->getPosition());
            }

            // Remove enemy if out of window bounds
            if (enemys[i]->getPosition().x <= 0 - enemys[i]->getBounds().width)
            {
                delete enemys[i];
                enemys.remove(i);
                return;
            }

            // Check enemy collision with players
            for (size_t j = 0; j < players.size(); j++)
            {
                if (enemys[i]->getBounds().intersects(players[j]->getBounds()))
                {
                    int damage = enemys[i]->getDamage();
                    players[j]->TakeDamage(damage);
                    this->textTags.add(TextTag(&this->font, '-' + std::to_string(damage),
                                               Vector2f(this->players[j]->getPosition().x + 10.f,
                                                        this->players[j]->getPosition().y - this->players[j]->getBounds().height / 2.f - 20.f),
                                               Vector2f(-1.f, 0.f),
                                               24, 20.f, true,
                                               Color::Red));
                    delete enemys[i];
                    enemys.remove(i);
                    if (players[j]->isDead())
                    {
                        players.erase(players.begin() + j);
                        if (players.empty())
                        {
                            this->gameOver = true;
                            return;
                        }
                        return;
                    }
                    break;
                }
            }
        }

        // Update text tags
        for (size_t i = 0; i < textTags.size(); i++)
        {
            textTags[i].Update(dt);
            if (textTags[i].getTimer() <= 0.f)
            {
                textTags.remove(i);
                break;
            }
        }
    }
    else
    {
        this->gameOverText.move(10.f * dt * dtMultiplier, 0.f);
        if (this->gameOverText.getPosition().x > this->window->getSize().x)
        {
            this->gameOverText.setPosition(
                0.f - this->gameOverText.getGlobalBounds().width,
                this->gameOverText.getPosition().y);
        }
    }
}

// Update player bullets
void Game::updateBullets(Player *p, const float &dt)
{
    if (p->getBulletSize() > 0)
    {
        for (size_t i = 0; i < p->getBulletSize(); i++)
        {
            bool flag = true;
            p->getBullet(i).Update(dt);

            // Bullet collision with window bounds
            if (p->getBullet(i).getPosition().x > this->window->getSize().x)
            {
                p->removeBullet(i);
                continue;
            }

            // Bullet collision with enemies
            for (size_t j = 0; j < enemys.size() && flag; j++)
            {
                if (p->getBullet(i).getBounds().intersects(enemys[j]->getBounds()))
                {
                    int damage = p->getBullet(i).getDamage();
                    enemys[j]->TakeDamage(damage);
                    this->textTags.add(TextTag(&this->font, '-' + std::to_string(damage),
                                               Vector2f(this->enemys[j]->getPosition().x + 10.f,
                                                        this->enemys[j]->getPosition().y - this->enemys[j]->getBounds().height / 2.f),
                                               Vector2f(1.f, 0.f),
                                               20.f, 30.f, true,
                                               Color::Red));
                    p->removeBullet(i);
                    flag = false;
                    if (enemys[j]->isDead())
                    {
                        handleEnemyDeath(p, j);
                        break;
                    }
                }
            }
        }
    }
}

// Update side gun bullets
void Game::updateSideGunBullets(Player *p, const float &dt)
{
    for (size_t j = 0; j < enemys.size(); j++)
    {
        for (size_t k = 0; k < p->getWeapons().size(); k++)
        {
            for (size_t l = 0; l < p->getWeapons()[k]->getBullets().size(); l++)
            {
                if (p->getWeapons()[k]->getBullets()[l]->getBounds().intersects(enemys[j]->getBounds()))
                {
                    int damage = p->getWeapons()[k]->getBullets()[l]->getDamage();
                    enemys[j]->TakeDamage(damage);
                    this->textTags.add(TextTag(&this->font, '-' + std::to_string(damage),
                                               Vector2f(this->enemys[j]->getPosition().x + 10.f,
                                                        this->enemys[j]->getPosition().y - this->enemys[j]->getBounds().height / 2.f),
                                               Vector2f(1.f, 0.f),
                                               20.f, 20.f, true,
                                               Color::Red));
                    delete p->getWeapons()[k]->getBullets()[l];
                    p->getWeapons()[k]->getBullets().erase(p->getWeapons()[k]->getBullets().begin() + l);
                    if (enemys[j]->isDead())
                    {
                        handleEnemyDeath(p, j);
                        return;
                    }
                }
            }
        }
    }
}

// Handle enemy death
void Game::handleEnemyDeath(Player *p, size_t enemyIndex)
{
    if (!p->getIsAtMaxLevel())
    {
        float exp = enemys[enemyIndex]->getExp();
        if (p->gainExp(exp))
        {
            this->textTags.add(TextTag(&this->font, "Level Up",
                                       Vector2f(p->getPosition().x,
                                                p->getPosition().y - p->getBounds().height / 2.f),
                                       Vector2f(0.f, 1.f),
                                       35.f, 30.f, true,
                                       Color::Green));
        }
        else
        {

            this->textTags.add(TextTag(&this->font, "+" + std::to_string(static_cast<int>(exp)) + " exp",
                                       Vector2f(p->getPosition().x,
                                                p->getPosition().y + p->getBounds().height / 2.f - 30.f),
                                       Vector2f(0.f, 1.f),
                                       25.f, 15.f, true,
                                       Color::Cyan));
        }
    }

    delete enemys[enemyIndex];
    enemys.remove(enemyIndex);
}

// Render UI elements
void Game::RenderUI()
{
    if (!gameOver)
    {
        for (size_t i = 0; i < players.size(); i++)
        {
            this->UpdateUI(i);
            this->window->draw(this->followPlayerText);
            this->window->draw(this->playerExpBar);
            this->window->draw(this->playerExpBarOutline);
            this->window->draw(this->playerLevelText);

            // Render text tags
            for (size_t i = 0; i < textTags.size(); ++i)
            {
                textTags[i].Render(*this->window);
            }
        }
    }
    else
    {
        this->window->draw(this->gameOverText);
    }
}

// Render game elements
void Game::Render()
{
    this->window->clear();
    if (!gameOver)
    {
        for (auto &p : players)
        {
            p->Render(*this->window);
        }

        // Render enemies
        for (size_t i = 0; i < enemys.size(); ++i)
        {
            enemys[i]->Render(*this->window);
        }
    }

    // Render UI
    this->RenderUI();

    this->window->display();
}
