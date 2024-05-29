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
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <vector>

using json = nlohmann::json;

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

    bool isReset = false;

    // Private member functions
    void loadTextures();
    void createPlayers();
    void updateBullets(Player *p, const float &dt);
    void updateSideGunBullets(Player *p, const float &dt);
    void handleEnemyDeath(Player *p, size_t enemyIndex);

public:
    // Constructor and Destructor
    Game(RenderWindow *window, int numberOfPlayers,
         int player1Level, int player1Hp, int player1HpMax, float player1Exp, float player1ExpNext, int player1Score,
         int player2Level, int player2Hp, int player2HpMax, float player2Exp, float player2ExpNext, int player2Score,
         bool upperWeapon, int upperWeaponLevel, bool lowerWeapon, int lowerWeaponLevel);
    virtual ~Game();

    // Accessors
    inline RenderWindow &getWindow() { return *this->window; }
    inline const bool &isGameOver() const { return this->gameOver; }
    inline const bool &isGamePaused() const { return this->gamePaused; }
    inline const bool &isInGame() const { return this->inGame; }
    inline void pause() { this->gamePaused = true; }
    inline void resume() { this->gamePaused = false; }
    inline bool hasBeenReset() { return this->isReset;}

    // Functions
    Player *createPlayer(DynamicArray<Texture> &textures, Vector2u windowBounds,
                         int level, float playerExp, float playerExpNext, int playerHp, int playerHpMax, int playerScore,
                         int upKey, int downKey, int leftKey, int rightKey, int fireKey);

    void getGameState(int &numberOfPlayers,
                      int &player1Level, int &player1Hp, int &player1HpMax, float &player1Exp, float &player1ExpNext, int &player1Score,
                      int &player2Level, int &player2Hp, int &player2HpMax, float &player2Exp, float &player2ExpNext, int &player2Score,
                      bool &upperWeapon, int &upperWeaponLevel,
                      bool &lowerWeapon, int &lowerWeaponLevel);

    // Modifying functions
    void setIsGameStarted(bool isGameStarted) { this->inGame = isGameStarted; }
    void setWeaponType(int weaponType)
    {
        this->players[0]->setCurrentWeapon(weaponType);
        if (this->numberOfPlayers == 2)
        {
            this->players[1]->setCurrentWeapon(weaponType);
        }
    }
    
    void setUpperWeapon(bool upperWeapon) { 
        this->upperWeapon = upperWeapon; 
        this->players[0]->setUperWeapon(upperWeapon);
        if (this->numberOfPlayers == 2)
        {
            this->players[1]->setUperWeapon(upperWeapon);
        
     }
    }
    void setLowerWeapon(bool lowerWeapon) { 
        this->lowerWeapon = lowerWeapon; 
        this->players[0]->setLowerWeapon(lowerWeapon);
        if (this->numberOfPlayers == 2)
        {
            this->players[1]->setLowerWeapon(lowerWeapon);
        }
    }
    void setUpperWeaponLevel(int upperWeaponLevel) { 
        this->upperWeaponLevel = upperWeaponLevel; 
        this->players[0]->setUpperWeaponLevel(upperWeaponLevel);
        if (this->numberOfPlayers == 2)
        {
            this->players[1]->setUpperWeaponLevel(upperWeaponLevel);
        }
    }
    void setLowerWeaponLevel(int lowerWeaponLevel) { 
        this->lowerWeaponLevel = lowerWeaponLevel; 
        this->players[0]->setLowerWeaponLevel(lowerWeaponLevel);
        if (this->numberOfPlayers == 2)
        {
            this->players[1]->setLowerWeaponLevel(lowerWeaponLevel);
        }
    }
    void reseted(bool reset) { this->isReset = reset; }

    void restart();
    void exit();

    void initUI();
    void updateUI(int index);
    void update(const float &dt);
    void renderUI();
    void render();
};
