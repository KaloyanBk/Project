/**
 * @file Game.cpp
 * @author Kaloyan
 * @brief This is the implementation file for the Game class, which is used to manage the game logic.
 *
 * The Game class is responsible for managing the game logic, including player and enemy interactions, bullet collisions, and UI elements.
 * @version 0.1
 * @date 2024-05-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "../include/Game.hpp"
#include <stdexcept>
#include <cassert>

/**
 * @brief Constructor for the Game class.
 *
 * Initializes the game with the specified settings for the window, players,
 * weapons, and game parameters.
 *
 * @param window Pointer to the SFML RenderWindow.
 * @param numberOfPlayers Number of players (1 or 2).
 * @param player1Level Level of player 1.
 * @param player1Hp Current health points of player 1.
 * @param player1HpMax Maximum health points of player 1.
 * @param player1Exp Current experience points of player 1.
 * @param player1ExpNext Experience points needed for player 1 to level up.
 * @param player1Score Current score of player 1.
 * @param player2Level Level of player 2.
 * @param player2Hp Current health points of player 2.
 * @param player2HpMax Maximum health points of player 2.
 * @param player2Exp Current experience points of player 2.
 * @param player2ExpNext Experience points needed for player 2 to level up.
 * @param player2Score Current score of player 2.
 * @param upperWeapon Indicates if the upper weapon is enabled.
 * @param upperWeaponLevel Level of the upper weapon.
 * @param lowerWeapon Indicates if the lower weapon is enabled.
 * @param lowerWeaponLevel Level of the lower weapon.
 * @param typeOfBullet Type of bullet used by the player(s).
 */
Game::Game(RenderWindow *window,
           int numberOfPlayers,
           int player1Level, int player1Hp, int player1HpMax, float player1Exp, float player1ExpNext, int player1Score,
           int player2Level, int player2Hp, int player2HpMax, float player2Exp, float player2ExpNext, int player2Score,
           bool upperWeapon, int upperWeaponLevel,
           bool lowerWeapon, int lowerWeaponLevel,
           int typeOfBullet)
    : window(window), numberOfPlayers(numberOfPlayers),
      player1Level(player1Level), player2Level(player2Level), upperWeaponLevel(upperWeaponLevel), lowerWeaponLevel(lowerWeaponLevel),
      upperWeapon(upperWeapon), lowerWeapon(lowerWeapon), player1Exp(player1Exp), player2Exp(player2Exp),
      player1ExpNext(player1ExpNext), player1Hp(player1Hp), player1HpMax(player1HpMax), player1Score(player1Score),
      player2ExpNext(player2ExpNext), player2Hp(player2Hp), player2HpMax(player2HpMax), player2Score(player2Score),
      typeOfBullet(typeOfBullet)
{
    try
    {
        /// Window settings
        this->dtMultiplier = 60.f;

        /// Load resources
        this->loadTextures();

        /// Create players
        this->createPlayers();

        /// Initialize enemy spawn timer
        this->enemySpawnTimerMax = 25.f;
        this->enemySpawnTimer = this->enemySpawnTimerMax;

        /// Initialize UI
        this->initUI();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error in Game constructor: " << e.what() << std::endl;
    }
}

/**
 * @brief Destructor for the Game class.
 *
 * Cleans up dynamically allocated memory for players and enemies.
 */
Game::~Game()
{
    /// Delete player objects
    for (auto &p : players)
    {
        delete p;
    }

    /// Delete enemy objects
    for (size_t i = 0; i < enemies.size(); ++i)
    {
        delete enemies[i];
    }

    /// Clear enemy and player vectors
    enemies.clear();
    players.clear();
}

/**
 * @brief Load textures from files and store them in the textures container.
 *
 * This function iterates through the resource paths, loads each texture from a file,
 * and adds it to the textures container. Throws a runtime_error if loading a texture fails.
 *
 * @throws std::runtime_error If a texture fails to load.
 */
void Game::loadTextures()
{
    /// Loop through the resource paths
    for (size_t i = 0; i < NUM_RESOURCES; ++i)
    {
        Texture texture;

        /// Load texture from file
        if (!texture.loadFromFile(resourcePaths.at(static_cast<Textures>(i))))
        {
            throw std::runtime_error("Failed to load texture: " + resourcePaths.at(static_cast<Textures>(i)));
        }

        /// Add texture to the textures container
        this->textures.add(texture);
    }
}

/// Create player
Player *Game::createPlayer(DynamicArray<Texture> &textures, Vector2u windowBounds,
                           int level, float playerExp, float playerExpNext, int playerHp, int playerHpMax, int playerScore,
                           int upKey, int downKey, int leftKey, int rightKey, int fireKey, int typeOfBullet)
{
    /// Check if the texture array is empty
    if (textures.size() == 0)
    {
        throw std::invalid_argument("Texture array is empty");
    }

    /**
     * @brief Create a new player with the specified parameters.
     *
     * This function creates a new player instance using the provided parameters,
     * including textures, window bounds, player statistics, and control keys.
     *
     * @param textures The array of textures to be used by the player.
     * @param windowBounds The bounds of the window in which the player will operate.
     * @param level The level of the player.
     * @param playerExp The experience points of the player.
     * @param playerExpNext The experience points required for the next level.
     * @param playerHp The current health points of the player.
     * @param playerHpMax The maximum health points of the player.
     * @param playerScore The score of the player.
     * @param upKey The key used to move up.
     * @param downKey The key used to move down.
     * @param leftKey The key used to move left.
     * @param rightKey The key used to move right.
     * @param fireKey The key used to fire.
     * @param typeOfBullet The type of bullet the player uses.
     *
     * @return Player* A pointer to the newly created player instance.
     * @throws std::invalid_argument If the texture array is empty.
     */
    return new Player(textures, windowBounds, typeOfBullet, upKey, downKey, leftKey, rightKey, fireKey,
                      level, playerExp, playerExpNext, playerHp, playerHpMax, playerScore,
                      this->upperWeaponLevel, this->lowerWeaponLevel, this->upperWeapon, this->lowerWeapon);
}

/**
 * @brief Create player instances based on the number of players.
 *
 * This function loads saved player data and creates player instances based on the
 * number of players specified. Players are configured with control keys and statistics.
 */
void Game::createPlayers()
{
    /// Load saved player data
    loadSavedData(this->numberOfPlayers,
                  this->player1Level, this->player1Hp, this->player1HpMax, this->player1Exp, this->player1ExpNext, this->player1Score,
                  this->player2Level, this->player2Hp, this->player2HpMax, this->player2Exp, this->player2ExpNext, this->player2Score,
                  this->upperWeapon, this->upperWeaponLevel,
                  this->lowerWeapon, this->lowerWeaponLevel,
                  this->typeOfBullet);

    /// Create players based on the number of players
    switch (numberOfPlayers)
    {
    case 1:
        /// Create player 1
        this->players.push_back(createPlayer(this->textures, this->window->getSize(),
                                             this->player1Level, this->player1Exp, this->player1ExpNext, this->player1Hp,
                                             this->player1HpMax, this->player1Score,
                                             Keyboard::W, Keyboard::S, Keyboard::A, Keyboard::D, Keyboard::Space, this->typeOfBullet));
        break;
    case 2:
        /// Create player 1
        this->players.push_back(createPlayer(this->textures, this->window->getSize(),
                                             this->player1Level, this->player1Exp, this->player1ExpNext, this->player1Hp,
                                             this->player1HpMax, this->player1Score,
                                             Keyboard::W, Keyboard::S, Keyboard::A, Keyboard::D, Keyboard::Space, this->typeOfBullet));
        /// Create player 2
        this->players.push_back(createPlayer(this->textures, this->window->getSize(),
                                             this->player2Level, this->player2Exp, this->player2ExpNext, this->player2Hp,
                                             this->player2HpMax, this->player2Score, Keyboard::Up, Keyboard::Down, Keyboard::Left, Keyboard::Right, Keyboard::RShift, this->typeOfBullet));
        break;
    default:
        /// Do nothing for invalid number of players
        break;
    }
}

/**
 * @brief Get the current game state including player information and weapon states.
 *
 * This function sets the provided references with the current game state information.
 * If the number of players is one, it throws an exception if player 2 is accessed.
 *
 * @param numberOfPlayers The reference to store the number of players.
 * @param player1Level The reference to store player 1's level.
 * @param player1Hp The reference to store player 1's current health points.
 * @param player1HpMax The reference to store player 1's maximum health points.
 * @param player1Exp The reference to store player 1's experience points.
 * @param player1ExpNext The reference to store player 1's experience points needed for the next level.
 * @param player1Score The reference to store player 1's score.
 * @param player2Level The reference to store player 2's level.
 * @param player2Hp The reference to store player 2's current health points.
 * @param player2HpMax The reference to store player 2's maximum health points.
 * @param player2Exp The reference to store player 2's experience points.
 * @param player2ExpNext The reference to store player 2's experience points needed for the next level.
 * @param player2Score The reference to store player 2's score.
 * @param upperWeapon The reference to store the state of the upper weapon.
 * @param upperWeaponLevel The reference to store the level of the upper weapon.
 * @param lowerWeapon The reference to store the state of the lower weapon.
 * @param lowerWeaponLevel The reference to store the level of the lower weapon.
 *
 * @throws std::runtime_error If player 1 or player 2 does not exist when expected.
 */
void Game::getGameState(int &numberOfPlayers,
                        int &player1Level, int &player1Hp, int &player1HpMax, float &player1Exp, float &player1ExpNext, int &player1Score,
                        int &player2Level, int &player2Hp, int &player2HpMax, float &player2Exp, float &player2ExpNext, int &player2Score,
                        bool &upperWeapon, int &upperWeaponLevel,
                        bool &lowerWeapon, int &lowerWeaponLevel)
{
    /// Set the number of players
    numberOfPlayers = this->numberOfPlayers;

    /// Get player 1 state
    if (this->players.size() > 0)
    {
        player1Level = this->players[0]->getLevel();
        player1Hp = this->players[0]->getHp();
        player1HpMax = this->players[0]->getHpMax();
        player1Exp = this->players[0]->getExp();
        player1ExpNext = this->players[0]->getExpNext();
        player1Score = this->players[0]->getScore();
    }
    else
    {
        throw std::runtime_error("Player 1 does not exist.");
    }

    /// Get player 2 state if there are two players
    if (this->numberOfPlayers == 2 && this->players.size() > 1)
    {
        player2Level = this->players[1]->getLevel();
        player2Hp = this->players[1]->getHp();
        player2HpMax = this->players[1]->getHpMax();
        player2Exp = this->players[1]->getExp();
        player2ExpNext = this->players[1]->getExpNext();
        player2Score = this->players[1]->getScore();
    }
    else if (this->numberOfPlayers == 2 && this->players.size() <= 1)
    {
        throw std::runtime_error("Player 2 does not exist.");
    }

    /// Get upper weapon state
    upperWeapon = this->upperWeapon;
    upperWeaponLevel = this->upperWeaponLevel;

    /// Get lower weapon state
    lowerWeapon = this->lowerWeapon;
    lowerWeaponLevel = this->lowerWeaponLevel;
}

void Game::loadSavedGameData(int numberOfPlayers,
                             int player1Level, int player1Hp, int player1HpMax, float player1Exp, float player1ExpNext, int player1Score,
                             int player2Level, int player2Hp, int player2HpMax, float player2Exp, float player2ExpNext, int player2Score,
                             bool upperWeapon, int upperWeaponLevel, bool lowerWeapon, int lowerWeaponLevel, int typeOfBullet)
{
    this->numberOfPlayers = numberOfPlayers;
    this->player1Level = player1Level;
    this->player2Level = player2Level;
    this->player1Hp = player1Hp;
    this->player2Hp = player2Hp;
    this->player1HpMax = player1HpMax;
    this->player2HpMax = player2HpMax;
    this->player1Exp = player1Exp;
    this->player2Exp = player2Exp;
    this->player1ExpNext = player1ExpNext;
    this->player2ExpNext = player2ExpNext;
    this->player1Score = player1Score;
    this->player2Score = player2Score;
    this->upperWeapon = upperWeapon;
    this->upperWeaponLevel = upperWeaponLevel;
    this->lowerWeapon = lowerWeapon;
    this->lowerWeaponLevel = lowerWeaponLevel;
    this->typeOfBullet = typeOfBullet;
}

void Game::setWeaponType(int weaponType)
{
    this->players[0]->setCurrentWeapon(weaponType);
    if (this->numberOfPlayers == 2)
    {
        this->players[1]->setCurrentWeapon(weaponType);
    }
}

void Game::setUpperWeapon(bool upperWeapon)
{
    this->upperWeapon = upperWeapon;
    this->players[0]->setUperWeapon(upperWeapon);
    if (this->numberOfPlayers == 2)
    {
        this->players[1]->setUperWeapon(upperWeapon);
    }
}

void Game::setLowerWeapon(bool lowerWeapon)
{
    this->lowerWeapon = lowerWeapon;
    this->players[0]->setLowerWeapon(lowerWeapon);
    if (this->numberOfPlayers == 2)
    {
        this->players[1]->setLowerWeapon(lowerWeapon);
    }
}

void Game::setUpperWeaponLevel(int upperWeaponLevel)
{
    this->upperWeaponLevel = upperWeaponLevel;
    this->players[0]->setUpperWeaponLevel(upperWeaponLevel);
    if (this->numberOfPlayers == 2)
    {
        this->players[1]->setUpperWeaponLevel(upperWeaponLevel);
    }
}

void Game::setLowerWeaponLevel(int lowerWeaponLevel)
{
    this->lowerWeaponLevel = lowerWeaponLevel;
    this->players[0]->setLowerWeaponLevel(lowerWeaponLevel);
    if (this->numberOfPlayers == 2)
    {
        this->players[1]->setLowerWeaponLevel(lowerWeaponLevel);
    }
}
/**
 * @brief Initialize the UI elements.
 *
 * This function loads the font, sets up text elements, progress bars, and initializes buttons
 * for restarting, exiting, and pausing the game.
 *
 * @throws std::runtime_error If the font fails to load.
 */
void Game::initUI()
{
    /// Load font for UI elements
    assert(this->font.loadFromFile(resourcePathsFonts.at(DOSIS_LIGHT)) && "Failed to load font");

    /// Set font for text elements
    this->followPlayerText.setFont(font);
    this->stationaryText.setFont(font);
    this->playerLevelText.setFont(font);

    /// Set character size and color for Follow Player Text
    this->followPlayerText.setCharacterSize(22);
    this->followPlayerText.setFillColor(Color::White);

    /// Set character size and color for Stationary Text
    this->stationaryText.setCharacterSize(12);
    this->stationaryText.setFillColor(Color::White);

    /// Set size, color, and outline for Player Exp Bar
    this->playerExpBar.setSize(Vector2f(110.f, 12.f));
    this->playerExpBar.setFillColor(Color(0.f, 100.f, 200.f, 200.f));

    this->playerExpBarOutline.setSize(Vector2f(110.f, 12.f));
    this->playerExpBarOutline.setFillColor(Color::Transparent);
    this->playerExpBarOutline.setOutlineThickness(1.f);
    this->playerExpBarOutline.setOutlineColor(Color::White);

    /// Set character size and color for Player Level Text
    this->playerLevelText.setCharacterSize(22);
    this->playerLevelText.setFillColor(Color::White);

    /// Create buttons
    float cornerRadius = 10.0f;

    /// Initialize Restart Button
    this->restartButton = new Button(
        this->window->getSize().x - 400, 50, 150, 50, cornerRadius,
        this->font, "Restart",
        sf::Color(70, 70, 70, 200),
        sf::Color(150, 150, 150, 200),
        sf::Color(20, 20, 20, 200));

    /// Initialize Exit Button
    this->exitButton = new Button(
        this->window->getSize().x - 200, 50, 150, 50, cornerRadius,
        this->font, "Exit",
        sf::Color(70, 70, 70, 200),
        sf::Color(150, 150, 150, 200),
        sf::Color(20, 20, 20, 200));

    /// Initialize Pause Button
    this->pauseButton = new Button(
        this->window->getSize().x - 600, 50, 150, 50, cornerRadius,
        this->font, "Pause",
        sf::Color(70, 70, 70, 200),
        sf::Color(150, 150, 150, 200),
        sf::Color(20, 20, 20, 200));

    /// Load font for game over text
    assert(this->gameOverFont.loadFromFile(resourcePathsFonts.at(GAME_OVER)) && "Failed to load font");

    /// Set font, size, color, and position for Game Over Text
    this->gameOverText.setFont(gameOverFont);
    this->gameOverText.setCharacterSize(60);
    this->gameOverText.setFillColor(Color::White);
    this->gameOverText.setString("Game Over");
    this->gameOverText.setPosition(
        0.f - this->gameOverText.getGlobalBounds().width,
        this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);
}

/**
 * @brief Update the UI elements for a specified player.
 *
 * This function updates the position and content of the UI elements (such as text and experience bar)
 * to reflect the current state of the specified player.
 *
 * @param index The index of the player whose UI elements are to be updated.
 *
 * @throws std::out_of_range If the player index is out of bounds.
 */
void Game::updateUI(int index)
{
    /// Assert that the player index is within bounds
    assert(index >= 0 && index < players.size() && "Player index out of bounds");

    /// Update UI elements for the specified player
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

    /// Exp Bar
    this->playerExpBar.setPosition(
        this->players[index]->getPosition().x - this->players[index]->getBounds().width / 2.f + 10.f,
        this->players[index]->getPosition().y + this->players[index]->getBounds().height / 2.f + 10.f);

    this->playerExpBarOutline.setPosition(this->playerExpBar.getPosition());
    this->playerExpBar.setScale(
        static_cast<float>(this->players[index]->getExp()) / static_cast<float>(this->players[index]->getExpNext()), 1.f);
}

/**
 * @brief Update the game state.
 *
 * This function handles the game logic, including player updates, enemy spawning and updates,
 * collision detection, and UI updates. It also manages the game over state and button interactions.
 *
 * @param dt Delta time since the last frame update.
 *
 * @throws std::runtime_error If there is an error in loading saved data or updating button states.
 */
void Game::update(const float &dt)
{
    try
    {
        /// Check if this is the first update
        if (timesPlayers++ < 1)
        {
            /// Load saved data and create players
            loadSavedData(this->numberOfPlayers,
                          this->player1Level, this->player1Hp, this->player1HpMax, this->player1Exp, this->player1ExpNext, this->player1Score,
                          this->player2Level, this->player2Hp, this->player2HpMax, this->player2Exp, this->player2ExpNext, this->player2Score,
                          this->upperWeapon, this->upperWeaponLevel,
                          this->lowerWeapon, this->lowerWeaponLevel,
                          this->typeOfBullet);

            /// Delete previous players
            for (auto &p : players)
            {
                delete p;
            }
            players.clear();

            /// Reset player count
            Player::players = 0;

            /// Create new players
            this->createPlayers();
        }

        if (!this->gamePaused)
        {
            /// Update game logic only if the game is not paused
            if (!gameOver)
            {
                /// Increment enemy spawn timer
                if (enemySpawnTimer < enemySpawnTimerMax)
                    enemySpawnTimer += 1.f * dt * this->dtMultiplier;

                /// Spawn new enemies if the spawn timer exceeds the maximum value
                if (enemySpawnTimer >= enemySpawnTimerMax)
                {
                    /// Function to generate random numbers with a 50/50 chance
                    auto random50_50 = []() -> int
                    {
                        return rand() % 2;
                    };

                    /// Spawn MoveLeftEnemy with a 50% chance
                    if (random50_50() == 0)
                    {
                        /// Randomize properties for MoveLeftEnemy
                        float spawnX = static_cast<float>(rand() % static_cast<int>(this->window->getSize().x));
                        float spawnY = static_cast<float>(rand() % static_cast<int>(this->window->getSize().y));
                        float directionX = -1.f;
                        float directionY = 0.f;
                        float scale = 0.4f + static_cast<float>((rand() % 20) / 100.0);
                        int hpMax = rand() % 3 + 1;
                        int damageMax = rand() % 5 + 1;
                        int damageMin = rand() % 3 + 1;
                        float exp = static_cast<float>(rand() % 10 + 1);

                        enemies.add(new MoveLeftEnemy(
                            &this->textures[ENEMY_MOVE_LEFT], this->window->getSize(),
                            Vector2f(spawnX, spawnY), Vector2f(directionX, directionY), Vector2f(scale, scale),
                            exp, hpMax, damageMax, damageMin));
                    }

                    /// Spawn FollowEnemy with a 50% chance
                    if (random50_50() == 0)
                    {
                        /// Randomize properties for FollowEnemy
                        float spawnX = static_cast<float>(rand() % static_cast<int>(this->window->getSize().x));
                        float spawnY = static_cast<float>(rand() % static_cast<int>(this->window->getSize().y));
                        float directionX = -1.f;
                        float directionY = 0.f;
                        float scale = 0.4f + static_cast<float>((rand() % 20) / 100.0);
                        int hpMax = rand() % 3 + 1;
                        int damageMax = rand() % 5 + 1;
                        int damageMin = rand() % 3 + 1;
                        float exp = static_cast<float>(rand() % 10 + 1);

                        int playerToFollow = random50_50();

                        enemies.add(new FollowEnemy(
                            &this->textures[ENEMY_FOLLOW], this->window->getSize(),
                            Vector2f(spawnX, spawnY), Vector2f(directionX, directionY), Vector2f(scale, scale),
                            exp, hpMax, damageMax, damageMin, playerToFollow));
                    }

                    /// Reset enemy spawn timer
                    enemySpawnTimer = 0;
                }

                /// Update players
                for (auto &p : players)
                {
                    p->Update(this->window->getSize(), dt);
                    this->updateBullets(p, dt);
                    this->updateSideGunBullets(p, dt);
                }

                /// Update enemies
                for (size_t i = 0; i < enemies.size(); i++)
                {
                    int followPlayerIndex = enemies[i]->getPlayerToFollow();
                    if (followPlayerIndex >= 0 && followPlayerIndex < players.size())
                    {
                        enemies[i]->Update(dt, players[followPlayerIndex]->getPosition());
                    }
                    else
                    {
                        /// Default behavior if player to follow is invalid
                        enemies[i]->Update(dt, players[0]->getPosition());
                    }

                    /// Remove enemy if out of window bounds
                    if (enemies[i]->getPosition().x <= 0 - enemies[i]->getBounds().width)
                    {
                        delete enemies[i];
                        enemies.remove(i);
                        continue; /// Continue to the next iteration to avoid accessing invalid memory
                    }

                    /// Check enemy collision with players
                    for (size_t j = 0; j < players.size(); j++)
                    {
                        if (enemies[i]->getBounds().intersects(players[j]->getBounds()))
                        {
                            int damage = enemies[i]->getDamage();
                            players[j]->TakeDamage(damage);
                            this->textTags.add(TextTag(&this->font, '-' + std::to_string(damage),
                                                       Vector2f(this->players[j]->getPosition().x + 10.f,
                                                                this->players[j]->getPosition().y - this->players[j]->getBounds().height / 2.f - 20.f),
                                                       Vector2f(-1.f, 0.f),
                                                       24, 20.f, true,
                                                       Color::Red));
                            delete enemies[i];
                            enemies.remove(i);
                            if (players[j]->isDead())
                            {
                                players.erase(players.begin() + j);
                                if (players.empty())
                                {
                                    this->gameOver = true;
                                    saveDefaultData();
                                    return;
                                }
                                continue;
                            }
                            break;
                        }
                    }
                }

                /// Update text tags
                for (size_t i = 0; i < textTags.size(); i++)
                {
                    textTags[i].Update(dt);
                    if (textTags[i].getTimer() <= 0.f)
                    {
                        textTags.remove(i);
                        continue;
                    }
                }
            }
            else
            {
                /// Move game over text
                this->gameOverText.move(10.f * dt * dtMultiplier, 0.f);
                if (this->gameOverText.getPosition().x > this->window->getSize().x)
                {
                    this->gameOverText.setPosition(
                        0.f - this->gameOverText.getGlobalBounds().width,
                        this->gameOverText.getPosition().y);
                }
            }
        }

        /// Update buttons
        if (restartButton == nullptr || exitButton == nullptr || pauseButton == nullptr)
        {
            throw std::runtime_error("One or more buttons are not initialized!");
        }

        /// Update button states based on mouse position
        restartButton->update(static_cast<Vector2f>(Mouse::getPosition(*this->window)));
        exitButton->update(static_cast<Vector2f>(Mouse::getPosition(*this->window)));
        pauseButton->update(static_cast<Vector2f>(Mouse::getPosition(*this->window)));

        /// Set button click actions
        restartButton->setOnClick([this]()
                                  { this->restart(); });

        exitButton->setOnClick([this]()
                               { this->exit(); });

        pauseButton->setOnClick([this]()
                                {
                                    std::cout << "Game Paused" << timesPressed << std::endl;
                                    if (this->timesPressed++ % 2 == 0)
                                    {
                                        this->pause();
                                    }
                                    else
                                    {
                                        this->resume();
                                    } });
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error in Game::update(): " << ex.what() << std::endl;
    }
}

/**
 * @brief Update player bullets.
 *
 * This function updates the position of each bullet fired by the player, checks for collisions
 * with enemies, and removes bullets that are out of bounds or have hit enemies.
 *
 * @param p Pointer to the player object.
 * @param dt Delta time since the last frame update.
 */
void Game::updateBullets(Player *p, const float &dt)
{
    try
    {
        if (p == nullptr)
        {
            throw std::invalid_argument("Player pointer is null!");
        }

        if (p->getBulletSize() > 0)
        {
            for (size_t i = 0; i < p->getBulletSize(); i++)
            {
                bool flag = true;
                p->getBullet(i).Update(dt);

                /// Bullet collision with window bounds
                if (p->getBullet(i).getPosition().x > this->window->getSize().x)
                {
                    p->removeBullet(i);
                    continue;
                }

                /// Bullet collision with enemies
                for (size_t j = 0; j < enemies.size() && flag; j++)
                {
                    if (enemies[j] == nullptr)
                    {
                        throw std::invalid_argument("Enemy pointer is null!");
                    }

                    if (p->getBullet(i).getBounds().intersects(enemies[j]->getBounds()))
                    {
                        int damage = p->getBullet(i).getDamage();
                        enemies[j]->TakeDamage(damage);
                        this->textTags.add(TextTag(&this->font, '-' + std::to_string(damage),
                                                   Vector2f(this->enemies[j]->getPosition().x + 10.f,
                                                            this->enemies[j]->getPosition().y - this->enemies[j]->getBounds().height / 2.f),
                                                   Vector2f(1.f, 0.f),
                                                   20.f, 30.f, true,
                                                   Color::Red));
                        p->removeBullet(i);
                        flag = false;
                        if (enemies[j]->isDead())
                        {
                            handleEnemyDeath(p, j);
                            break;
                        }
                    }
                }
            }
        }
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error in Game::updateBullets(): " << ex.what() << std::endl;
    }
}

/**
 * @brief Update side gun bullets.
 *
 * This function updates the position of each bullet fired by the player's side guns, checks for collisions
 * with enemies, and removes bullets that have hit enemies.
 *
 * @param p Pointer to the player object.
 * @param dt Delta time since the last frame update.
 */
void Game::updateSideGunBullets(Player *p, const float &dt)
{
    try
    {
        if (p == nullptr)
        {
            throw std::invalid_argument("Player pointer is null!");
        }

        for (size_t j = 0; j < enemies.size(); j++)
        {
            if (enemies[j] == nullptr)
            {
                throw std::invalid_argument("Enemy pointer is null!");
            }

            for (size_t k = 0; k < p->getWeapons().size(); k++)
            {
                if (p->getWeapons()[k] == nullptr)
                {
                    throw std::invalid_argument("Weapon pointer is null!");
                }

                for (size_t l = 0; l < p->getWeapons()[k]->getBullets().size(); l++)
                {
                    if (p->getWeapons()[k]->getBullets()[l] == nullptr)
                    {
                        throw std::invalid_argument("Bullet pointer is null!");
                    }

                    if (p->getWeapons()[k]->getBullets()[l]->getBounds().intersects(enemies[j]->getBounds()))
                    {
                        int damage = p->getWeapons()[k]->getBullets()[l]->getDamage();
                        enemies[j]->TakeDamage(damage);
                        this->textTags.add(TextTag(&this->font, '-' + std::to_string(damage),
                                                   Vector2f(this->enemies[j]->getPosition().x + 10.f,
                                                            this->enemies[j]->getPosition().y - this->enemies[j]->getBounds().height / 2.f),
                                                   Vector2f(1.f, 0.f),
                                                   20.f, 20.f, true,
                                                   Color::Red));
                        delete p->getWeapons()[k]->getBullets()[l];
                        p->getWeapons()[k]->getBullets().erase(p->getWeapons()[k]->getBullets().begin() + l);
                        if (enemies[j]->isDead())
                        {
                            handleEnemyDeath(p, j);
                            return;
                        }
                    }
                }
            }
        }
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error in Game::updateSideGunBullets(): " << ex.what() << std::endl;
    }
}

/**
 * @brief Handle enemy death.
 *
 * This function is called when an enemy dies. It updates the player's experience points,
 * displays text tags indicating level up or gained experience, and removes the enemy object.
 *
 * @param p Pointer to the player object.
 * @param enemyIndex Index of the enemy in the enemies vector.
 */

void Game::handleEnemyDeath(Player *p, size_t enemyIndex)
{
    try
    {
        /// Check if the player pointer is null
        if (p == nullptr)
        {
            throw std::invalid_argument("Player pointer is null!");
        }

        /// Check if the enemy index is out of bounds
        if (enemyIndex >= enemies.size())
        {
            throw std::out_of_range("Enemy index out of bounds!");
        }

        /// Check if the player is not at max level
        if (!p->getIsAtMaxLevel())
        {
            float exp = enemies[enemyIndex]->getExp();
            if (p->gainExp(exp))
            {
                /// Add a text tag indicating level up
                this->textTags.add(TextTag(&this->font, "Level Up",
                                           Vector2f(p->getPosition().x,
                                                    p->getPosition().y - p->getBounds().height / 2.f),
                                           Vector2f(0.f, 1.f),
                                           35.f, 30.f, true,
                                           Color::Green));
            }
            else
            {
                /// Add a text tag indicating gained experience
                this->textTags.add(TextTag(&this->font, "+" + std::to_string(static_cast<int>(exp)) + " exp",
                                           Vector2f(p->getPosition().x,
                                                    p->getPosition().y + p->getBounds().height / 2.f - 30.f),
                                           Vector2f(0.f, 1.f),
                                           25.f, 15.f, true,
                                           Color::Cyan));
            }
        }

        /// Delete the enemy object and remove it from the vector
        delete enemies[enemyIndex];
        enemies.remove(enemyIndex);
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error in Game::handleEnemyDeath(): " << ex.what() << std::endl;
    }
}

/**
 * @brief Restart the game.
 *
 * This function clears all current players and enemies, resets the game state, reloads saved data,
 * and recreates players. It also decrements the times counter and emits a signal indicating the game reset.
 *
 * @throws std::runtime_error If loading saved data fails.
 */
void Game::restart()
{
    /// Delete existing player objects
    for (auto &p : players)
    {
        delete p;
    }
    players.clear();

    /// Delete existing enemy objects
    for (size_t i = 0; i < enemies.size(); ++i)
    {
        delete enemies[i];
    }
    enemies.clear();

    /// Reset game over state and position of game over text
    this->gameOver = false;
    this->gameOverText.setPosition(
        0.f - this->gameOverText.getGlobalBounds().width,
        this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

    /// Save default data and load saved data
    saveDefaultData();
    try
    {
        loadSavedData(this->numberOfPlayers,
                      this->player1Level, this->player1Hp, this->player1HpMax, this->player1Exp, this->player1ExpNext, this->player1Score,
                      this->player2Level, this->player2Hp, this->player2HpMax, this->player2Exp, this->player2ExpNext, this->player2Score,
                      this->upperWeapon, this->upperWeaponLevel,
                      this->lowerWeapon, this->lowerWeaponLevel,
                      this->typeOfBullet);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error(std::string("Failed to load data: ") + e.what());
    }

    /// Reset player count
    Player::players = 0;

    /// Create players
    createPlayers();

    /// Decrement times and set game started state
    this->times--;
    this->setIsGameStarted(true);

    /// Emit signal indicating game reset
    this->reseted(true);
}

/**
 * @brief Exit the game.
 *
 * This function closes the game window and saves the current game data for the number of players.
 *
 * @throws std::runtime_error If saving data fails.
 */
void Game::exit()
{
    /// Close the game window
    this->window->close();

    /// Save game data based on the number of players
    try
    {
        if (this->numberOfPlayers == 1)
        {
            saveData(
                this->numberOfPlayers,
                this->players[0]->getLevel(), this->players[0]->getHp(), this->players[0]->getHpMax(), this->players[0]->getExp(), this->players[0]->getExpNext(), this->players[0]->getScore(),
                0, 10, 0, 0.0, 0.0, 0,
                this->upperWeapon, this->upperWeaponLevel,
                this->lowerWeapon, this->lowerWeaponLevel,
                this->typeOfBullet);
        }
        else if (this->numberOfPlayers == 2)
        {
            saveData(
                this->numberOfPlayers,
                this->players[0]->getLevel(), this->players[0]->getHp(), this->players[0]->getHpMax(), this->players[0]->getExp(), this->players[0]->getExpNext(), this->players[0]->getScore(),
                this->players[1]->getLevel(), this->players[1]->getHp(), this->players[1]->getHpMax(), this->players[1]->getExp(), this->players[1]->getExpNext(), this->players[1]->getScore(),
                this->upperWeapon, this->upperWeaponLevel,
                this->lowerWeapon, this->lowerWeaponLevel,
                this->typeOfBullet);
        }
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error(std::string("Failed to save data: ") + e.what());
    }
}

/**
 * @brief Render UI elements.
 *
 * This function renders all UI elements including text tags and buttons.
 */
void Game::renderUI()
{
    try
    {
        /// Check if the window pointer is null
        if (this->window == nullptr)
        {
            throw std::invalid_argument("Window pointer is null!");
        }

        /// Check if the game is not over
        if (!gameOver)
        {
            /// Render UI elements for each player
            for (size_t i = 0; i < players.size(); i++)
            {
                this->updateUI(i);
                this->window->draw(this->followPlayerText);
                this->window->draw(this->playerExpBar);
                this->window->draw(this->playerExpBarOutline);
                this->window->draw(this->playerLevelText);
                /// Render text tags
                for (size_t j = 0; j < textTags.size(); ++j)
                {
                    textTags[j].Render(*this->window);
                }
            }
        }
        else
        {
            this->window->draw(this->gameOverText);
        }

        /// Check if any button pointer is null
        if (this->restartButton == nullptr || this->exitButton == nullptr || this->pauseButton == nullptr)
        {
            throw std::runtime_error("One or more button pointers are null!");
        }

        /// Render buttons
        this->restartButton->render(*this->window);
        this->exitButton->render(*this->window);
        this->pauseButton->render(*this->window);
    }
    catch (const std::exception &ex)
    {
        /// Handle any exceptions and print error messages
        std::cerr << "Error in Game::renderUI(): " << ex.what() << std::endl;
    }
}

/**
 * @brief Renders the game elements.
 *
 * This method renders the game elements, including players, enemies, and UI components.
 * It checks for null pointers and handles exceptions appropriately.
 */
void Game::render()
{
    try
    {
        /// Check if the window pointer is null
        if (this->window == nullptr)
        {
            throw std::invalid_argument("Window pointer is null!");
        }

        this->window->clear();

        /// Check if the game is not over
        if (!gameOver)
        {
            /// Render players
            for (auto &p : players)
            {
                if (p == nullptr)
                {
                    std::cerr << "Error: Player pointer is null!" << std::endl;
                    continue;
                }
                p->Render(*this->window);
            }

            /// Render enemies
            for (size_t i = 0; i < enemies.size(); ++i)
            {
                if (enemies[i] == nullptr)
                {
                    std::cerr << "Error: Enemy pointer at index " << i << " is null!" << std::endl;
                    continue;
                }
                enemies[i]->Render(*this->window);
            }
        }

        /// Render UI elements
        this->renderUI();

        this->window->display();
    }
    catch (const std::exception &ex)
    {
        /// Handle any exceptions and print error messages
        std::cerr << "Error in Game::render(): " << ex.what() << std::endl;
    }
}
