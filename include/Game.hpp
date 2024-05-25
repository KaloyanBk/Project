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

public:
    // Constructor and Destructor
    Game(RenderWindow *window);
    virtual ~Game();

    // Accessors
    inline RenderWindow &getWindow() { return *this->window; }

    // Functions
    Player *createPlayer(DynamicArray<Texture> &textures, Vector2u windowBounds,
                         int upKey, int downKey, int leftKey, int rightKey, int fireKey);
    void InItUi();
    void UpdateUI(int index);
    void Update(const float &dt);
    void RenderUI();
    void Render();
};