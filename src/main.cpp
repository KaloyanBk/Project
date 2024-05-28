#include <nlohmann/json.hpp>
#include <fstream>
#include "../include/Game.hpp"
#include <iostream>

using json = nlohmann::json;

void loadSavedData(
    int &numberOfPlayers,
    int &player1Level, int &player1Hp, int &player1HpMax, float &player1Exp, float &player1ExpNext, int &player1Score,
    int &player2Level, int &player2Hp, int &player2HpMax, float &player2Exp, float &player2ExpNext, int &player2Score,
    bool &upperWeapon, int &upperWeaponLevel,
    bool &lowerWeapon, int &lowerWeaponLevel)
{
    std::ifstream file("data/savedData.json");
    if (!file.is_open())
    {
        std::cerr << "Could not open the file!" << std::endl;
        return;
    }

    json savedData;
    file >> savedData;

    numberOfPlayers = savedData["numberOfPlayers"];
    
    player1Level = savedData["player1"]["level"];
    player1Hp = savedData["player1"]["hp"];
    player1HpMax = savedData["player1"]["hpMax"];
    player1Exp = savedData["player1"]["exp"];
    player1ExpNext = savedData["player1"]["expNext"];
    player1Score = savedData["player1"]["score"];

    player2Level = savedData["player2"]["level"];
    player2Hp = savedData["player2"]["hp"];
    player2HpMax = savedData["player2"]["hpMax"];
    player2Exp = savedData["player2"]["exp"];
    player2ExpNext = savedData["player2"]["expNext"];
    player2Score = savedData["player2"]["score"];

    upperWeapon = savedData["upperWeapon"]["enabled"];
    upperWeaponLevel = savedData["upperWeapon"]["level"];

    lowerWeapon = savedData["lowerWeapon"]["enabled"];
    lowerWeaponLevel = savedData["lowerWeapon"]["level"];
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    unsigned int screenWidth = desktop.width;
    unsigned int screenHeight = desktop.height;
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Fullscreen Window", sf::Style::Fullscreen);

    if (!window.isOpen())
    {
        // Handle window creation failure
        std::cerr << "Failed to create window!" << std::endl;
        return EXIT_FAILURE;
    }

    Clock clock;
    float dt = 0.f;

    int numberOfPlayers;

    int player1Level;
    int player1Hp;
    int player1HpMax;
    float player1Exp;
    float player1ExpNext;
    int player1Score;

    int player2Level;
    int player2Hp;
    int player2HpMax;
    float player2Exp;
    float player2ExpNext;
    int player2Score;

    bool upperWeapon;
    int upperWeaponLevel;

    bool lowerWeapon;
    int lowerWeaponLevel;

    // Load saved data
    loadSavedData(
        numberOfPlayers,
        player1Level, player1Hp, player1HpMax, player1Exp, player1ExpNext, player1Score,
        player2Level, player2Hp, player2HpMax, player2Exp, player2ExpNext, player2Score,
        upperWeapon, upperWeaponLevel,
        lowerWeapon, lowerWeaponLevel
    );

    Game game(&window, numberOfPlayers,
              player1Level, player1Hp, player1HpMax, player1Exp, player1ExpNext, player1Score,
              player2Level, player2Hp, player2HpMax, player2Exp, player2ExpNext, player2Score,
              upperWeapon, upperWeaponLevel,
              lowerWeapon, lowerWeaponLevel);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
        }

        // Update dt
        dt = clock.restart().asSeconds();

        // Update
        game.Update(dt);

        // Render
        game.Render();
    }

    return EXIT_SUCCESS;
}
