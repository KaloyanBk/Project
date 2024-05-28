#pragma once

#include "Player.hpp"
#include "./Resources/Fonts.hpp"
#include "./Resources/Textures.hpp"
#include "./Enemys/Enemy.hpp"
#include "./Enemys/MoveLeft.hpp"
#include "./Enemys/Follow.hpp"
#include "TextTag.hpp"

class Game
{
private:
    RenderWindow *window;
    float dtMultiplier;
    bool gameOver = false;

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

    // Resources
    DynamicArray<Texture> textures;

    // Players
    std::vector<Player *> players;

    // Enemies
    DynamicArray<Enemy *> enemys;
    float enemySpawnTimer;
    float enemySpawnTimerMax;

    // Private member functions
    void loadTextures();
    void createPlayers();
    void updateBullets(Player *p, const float &dt);
    void updateSideGunBullets(Player *p, const float &dt);
    void handleEnemyDeath(Player *p, size_t enemyIndex);

    // Load game progress
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

public:
    // Constructor and Destructor
    Game(RenderWindow *window,
         int numberOfPlayers,
         int player1Level, int player1Hp, int player1HpMax, float player1Exp, float player1ExpNext, int player1Score,
         int player2Level, int player2Hp, int player2HpMax, float player2Exp, float player2ExpNext, int player2Score,
         bool upperWeaponint, int upperWeaponLevel,
         bool lowerWeapon, int lowerWeaponLevel);
    virtual ~Game();

    // Accessors
    inline RenderWindow &getWindow() { return *this->window; }

    // Functions
    Player *createPlayer(DynamicArray<Texture> &textures, Vector2u windowBounds,
                         int level, float playerExp, float playerExpNext, int playerHp, int playerHpMax, int playerScore,
                         int upKey, int downKey, int leftKey, int rightKey, int fireKey);
    void InItUi();
    void UpdateUI(int index);
    void Update(const float &dt);
    void RenderUI();
    void Render();
};