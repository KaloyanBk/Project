#pragma once

// Include necessary headers
#include "Player.hpp"
#include "./Resources/Fonts.hpp"
#include "./Resources/Textures.hpp"
#include "./Enemys/Enemy.hpp"
#include "./Enemys/MoveLeft.hpp"
#include "./Enemys/Follow.hpp"
#include "../include/Weapons/PeaShooter.hpp"
#include "TextTag.hpp"
#include "./Resources/Button.hpp"
#include <iostream>
#include <vector>

class Game
{
private:
    // Private member variables
    RenderWindow *window;
    float dtMultiplier;
    bool gameOver = false;
    bool gamePaused = false;
    bool inGame = false;
    int timesPressed = 0;

    // UI elements
    Text followPlayerText;
    Text stationaryText;
    Text gameOverText;
    Text playerLevelText;
    DynamicArray<TextTag> textTags;

    // Fonts
    Font font;
    Font gameOverFont;

    // Bars
    RectangleShape playerHealthBar;
    RectangleShape playerExpBar;
    RectangleShape playerExpBarOutline;

    // Buttons
    Button *restartButton;
    Button *exitButton;
    Button *pauseButton;

    // Resources
    DynamicArray<Texture> textures;

    // Players
    std::vector<Player *> players;

    // Enemies
    DynamicArray<Enemy *> enemies;
    float enemySpawnTimer;
    float enemySpawnTimerMax;

    // Game state variables
    int numberOfPlayers;
    int player1Level;
    int player2Level;
    int upperWeaponLevel;
    int lowerWeaponLevel;
    bool upperWeapon;
    bool lowerWeapon;
    float player1Exp;
    float player2Exp;
    float player1ExpNext;
    float player2ExpNext;
    int player1Hp;
    int player2Hp;
    int player1HpMax;
    int player2HpMax;
    int player1Score;
    int player2Score;

    int typeOfBullet;

    bool isReset = false;
    bool countinue = false;

    // Private member functions
    void loadTextures();
    void createPlayers();
    void updateBullets(Player *p, const float &dt);
    void updateSideGunBullets(Player *p, const float &dt);
    void handleEnemyDeath(Player *p, size_t enemyIndex);

public:
    int times = 0;
    int timesPlayers = 0;
    // Constructor and Destructor
    Game(RenderWindow *window, int numberOfPlayers,
         int player1Level, int player1Hp, int player1HpMax, float player1Exp, float player1ExpNext, int player1Score,
         int player2Level, int player2Hp, int player2HpMax, float player2Exp, float player2ExpNext, int player2Score,
         bool upperWeapon, int upperWeaponLevel, bool lowerWeapon, int lowerWeaponLevel,
         int typeOfBullet);
    virtual ~Game();

    // Accessors
    inline RenderWindow &getWindow() { return *this->window; }
    inline const bool &isGameOver() const { return this->gameOver; }
    inline const bool &isGamePaused() const { return this->gamePaused; }
    inline const bool &isInGame() const { return this->inGame; }
    inline void pause() { this->gamePaused = true; }
    inline void resume() { this->gamePaused = false; }
    inline bool hasBeenReset() { return this->isReset; }
    inline bool isCountinue() { return this->countinue; }

    inline const int &getNumberOfPlayers() const { return this->numberOfPlayers; }
    inline const int &getPlayer1Level() const { return this->player1Level; }
    inline const int &getPlayer2Level() const { return this->player2Level; }
    inline const int &getPlayer1Hp() const { return this->player1Hp; }
    inline const int &getPlayer2Hp() const { return this->player2Hp; }
    inline const int &getPlayer1HpMax() const { return this->player1HpMax; }
    inline const int &getPlayer2HpMax() const { return this->player2HpMax; }
    inline const float &getPlayer1Exp() const { return this->player1Exp; }
    inline const float &getPlayer2Exp() const { return this->player2Exp; }
    inline const float &getPlayer1ExpNext() const { return this->player1ExpNext; }
    inline const float &getPlayer2ExpNext() const { return this->player2ExpNext; }
    inline const int &getPlayer1Score() const { return this->player1Score; }
    inline const int &getPlayer2Score() const { return this->player2Score; }
    inline const bool &getUpperWeapon() const { return this->upperWeapon; }
    inline const bool &getLowerWeapon() const { return this->lowerWeapon; }
    inline const int &getUpperWeaponLevel() const { return this->upperWeaponLevel; }
    inline const int &getLowerWeaponLevel() const { return this->lowerWeaponLevel; }
    inline const int getBulletType() const { return this->players[0]->getCurrentWeapon(); }

    // Functions
    Player *createPlayer(DynamicArray<Texture> &textures, Vector2u windowBounds,
                         int level, float playerExp, float playerExpNext, int playerHp, int playerHpMax, int playerScore,
                         int upKey, int downKey, int leftKey, int rightKey, int fireKey, int typeOfBullet);

    void getGameState(int &numberOfPlayers,
                      int &player1Level, int &player1Hp, int &player1HpMax, float &player1Exp, float &player1ExpNext, int &player1Score,
                      int &player2Level, int &player2Hp, int &player2HpMax, float &player2Exp, float &player2ExpNext, int &player2Score,
                      bool &upperWeapon, int &upperWeaponLevel,
                      bool &lowerWeapon, int &lowerWeaponLevel);

    // Modifying functions
    void loadSavedGameData(int numberOfPlayers,
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
    void setIsGameStarted(bool isGameStarted) { this->inGame = isGameStarted; }
    void setWeaponType(int weaponType)
    {
        this->players[0]->setCurrentWeapon(weaponType);
        if (this->numberOfPlayers == 2)
        {
            this->players[1]->setCurrentWeapon(weaponType);
        }
    }

    void setUpperWeapon(bool upperWeapon)
    {
        this->upperWeapon = upperWeapon;
        this->players[0]->setUperWeapon(upperWeapon);
        if (this->numberOfPlayers == 2)
        {
            this->players[1]->setUperWeapon(upperWeapon);
        }
    }
    void setLowerWeapon(bool lowerWeapon)
    {
        this->lowerWeapon = lowerWeapon;
        this->players[0]->setLowerWeapon(lowerWeapon);
        if (this->numberOfPlayers == 2)
        {
            this->players[1]->setLowerWeapon(lowerWeapon);
        }
    }
    void setUpperWeaponLevel(int upperWeaponLevel)
    {
        this->upperWeaponLevel = upperWeaponLevel;
        this->players[0]->setUpperWeaponLevel(upperWeaponLevel);
        if (this->numberOfPlayers == 2)
        {
            this->players[1]->setUpperWeaponLevel(upperWeaponLevel);
        }
    }
    void setLowerWeaponLevel(int lowerWeaponLevel)
    {
        this->lowerWeaponLevel = lowerWeaponLevel;
        this->players[0]->setLowerWeaponLevel(lowerWeaponLevel);
        if (this->numberOfPlayers == 2)
        {
            this->players[1]->setLowerWeaponLevel(lowerWeaponLevel);
        }
    }
    // seters
    void reseted(bool reset) { this->isReset = reset; }

    void restart();
    void exit();

    void initUI();
    void updateUI(int index);
    void update(const float &dt);
    void renderUI();
    void render();
};
