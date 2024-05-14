#pragma once

#include "Player.hpp"
#include "./Resources/Fonts.hpp"
#include "./Resources/Textures.hpp"
#include "./Enemys/Enemy.hpp"

class Game
{
private:
    RenderWindow *window;

    // UI
    std::vector<Text> followPlayerTexts;
    std::vector<Text> stationaryTexts;

    // Resources
    Font font;
    std::vector<Texture> textures;

    // Players
    std::vector<Player *> players;

    // Enemies
    std::vector<Enemy *> enemys;
    int enemySpawnTimer;
    int enemySpawnTimerMax;

    // Private member functions
    void loadTextures();
    void loadResources();
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
    void UpdateUI();
    void Update();
    void RenderUI();
    void Render();
};

// Enumerations
