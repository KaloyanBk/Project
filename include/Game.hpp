#pragma once

#include "Player.hpp"
#include "./Resources/Fonts.hpp"
#include "./Resources/Textures.hpp"
#include "./Enemys/Enemy.hpp"

class Game
{
private:
    RenderWindow *window;
    float dtMultiplier;
    bool gameOver = false;

    // UI
    // Texts
    Text followPlayerText;
    Text stationaryText;
    Text gameOverText;
    Text playerLevelText;

    std::vector<TextTag> textTags;

    // Fonts
    Font font;
    Font gameOverFont;

    // Barrs
    RectangleShape playerHealthBar;
    RectangleShape playerExpBar;
    RectangleShape playerExpBarOutline;


    // Resources
    std::vector<Texture> textures;

    // Players
    std::vector<Player *> players;

    // Enemies
    std::vector<Enemy *> enemys;
    float enemySpawnTimer;
    float enemySpawnTimerMax;

    // Private member functions
    void loadTextures();
    void createPlayers();

public:
    Game(RenderWindow *window);
    virtual ~Game();

    // Accessors
    inline RenderWindow &getWindow() { return *this->window; }

    // Functions
    Player *createPlayer(std::vector<Texture> &textures, Vector2u windowBounds,
                         int upKey, int downKey, int leftKey, int rightKey, int fireKey);
    void InItUi();
    void UpdateUI(int index);
    void Update(const float &dt);
    void RenderUI();
    void Render();
};

// Enumerations
