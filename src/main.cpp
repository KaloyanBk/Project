#include <nlohmann/json.hpp>
#include <fstream>
#include "../include/Game.hpp"
#include "../include/Menu.hpp"
#include <iostream>

using json = nlohmann::json;

void saveData(
    int numberOfPlayers,
    int player1Level, int player1Hp, int player1HpMax, float player1Exp, float player1ExpNext, int player1Score,
    int player2Level, int player2Hp, int player2HpMax, float player2Exp, float player2ExpNext, int player2Score,
    bool upperWeapon, int upperWeaponLevel,
    bool lowerWeapon, int lowerWeaponLevel)
{
    json savedData;

    savedData["numberOfPlayers"] = numberOfPlayers;

    savedData["player1"]["level"] = player1Level;
    savedData["player1"]["hp"] = player1Hp;
    savedData["player1"]["hpMax"] = player1HpMax;
    savedData["player1"]["exp"] = player1Exp;
    savedData["player1"]["expNext"] = player1ExpNext;
    savedData["player1"]["score"] = player1Score;

    savedData["player2"]["level"] = player2Level;
    savedData["player2"]["hp"] = player2Hp;
    savedData["player2"]["hpMax"] = player2HpMax;
    savedData["player2"]["exp"] = player2Exp;
    savedData["player2"]["expNext"] = player2ExpNext;
    savedData["player2"]["score"] = player2Score;

    savedData["upperWeapon"]["enabled"] = upperWeapon;
    savedData["upperWeapon"]["level"] = upperWeaponLevel;

    savedData["lowerWeapon"]["enabled"] = lowerWeapon;
    savedData["lowerWeapon"]["level"] = lowerWeaponLevel;

    std::ofstream file("data/savedData.json");
    if (!file.is_open())
    {
        std::cerr << "Could not open the file!" << std::endl;
        return;
    }

    file << savedData.dump(4);
}

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

    sf::Clock clock;
    bool wasInGame = false; // Track if the game was active in the previous frame

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
        lowerWeapon, lowerWeaponLevel);

    Game game(&window, numberOfPlayers,
              player1Level, player1Hp, player1HpMax, player1Exp, player1ExpNext, player1Score,
              player2Level, player2Hp, player2HpMax, player2Exp, player2ExpNext, player2Score,
              upperWeapon, upperWeaponLevel,
              lowerWeapon, lowerWeaponLevel);

    Menu menu(&window, &game);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) && !game.isGameOver())
            {
                // Extract current game state before saving
                game.getGameState(numberOfPlayers,
                                  player1Level, player1Hp, player1HpMax, player1Exp, player1ExpNext, player1Score,
                                  player2Level, player2Hp, player2HpMax, player2Exp, player2ExpNext, player2Score,
                                  upperWeapon, upperWeaponLevel,
                                  lowerWeapon, lowerWeaponLevel);

                saveData(
                    numberOfPlayers,
                    player1Level, player1Hp, player1HpMax, player1Exp, player1ExpNext, player1Score,
                    player2Level, player2Hp, player2HpMax, player2Exp, player2ExpNext, player2Score,
                    upperWeapon, upperWeaponLevel,
                    lowerWeapon, lowerWeaponLevel);

                window.close();
            }
        }

        // Update dt
        float dt = clock.restart().asSeconds();

        // Update
        if (!game.isInGame())
        {
            menu.update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)), event);
        }
        else
        {
            game.update(dt);
        }


        if (!game.isInGame())
        {
            menu.render(window);
        }
        else
        {
            game.render();
        }

    }

    return EXIT_SUCCESS;
}
