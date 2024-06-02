/**
 * @file Game.hpp
 * @author Kaloyan
 * @brief This is the header file for the Game class, which is used to create the game and manage the game state.
 * @version 0.1
 * @date 2024-05-30
 *
 * @copyright Copyright (c) 2024
 *
 */
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

    inline const bool &isGameOver() const { return this->gameOver; }
    inline const bool &isGamePaused() const { return this->gamePaused; }
    inline const bool &isInGame() const { return this->inGame; }
    inline bool hasBeenReset() { return this->isReset; }
    inline bool isCountinue() { return this->countinue; }
    inline void pause() { this->gamePaused = true; }
    inline void resume() { this->gamePaused = false; }


    // Modifying functions
    void setIsGameStarted(bool isGameStarted) { this->inGame = isGameStarted; }
    void setWeaponType(int weaponType);
    void setUpperWeapon(bool upperWeapon);
    void setLowerWeapon(bool lowerWeapon);
    void setUpperWeaponLevel(int upperWeaponLevel);
    void setLowerWeaponLevel(int lowerWeaponLevel);

    // Functions
    Player *createPlayer(DynamicArray<Texture> &textures, Vector2u windowBounds,
                         int level, float playerExp, float playerExpNext, int playerHp, int playerHpMax, int playerScore,
                         int upKey, int downKey, int leftKey, int rightKey, int fireKey, int typeOfBullet);

    void getGameState(int &numberOfPlayers,
                      int &player1Level, int &player1Hp, int &player1HpMax, float &player1Exp, float &player1ExpNext, int &player1Score,
                      int &player2Level, int &player2Hp, int &player2HpMax, float &player2Exp, float &player2ExpNext, int &player2Score,
                      bool &upperWeapon, int &upperWeaponLevel,
                      bool &lowerWeapon, int &lowerWeaponLevel);
    void loadSavedGameData(int numberOfPlayers,
                           int player1Level, int player1Hp, int player1HpMax, float player1Exp, float player1ExpNext, int player1Score,
                           int player2Level, int player2Hp, int player2HpMax, float player2Exp, float player2ExpNext, int player2Score,
                           bool upperWeapon, int upperWeaponLevel, bool lowerWeapon, int lowerWeaponLevel, int typeOfBullet);
    
    void reseted(bool reset) { this->isReset = reset; }
    void restart();
    void exit();

    void initUI();
    void updateUI(int index);
    void update(const float &dt);
    void renderUI();
    void render();
};
