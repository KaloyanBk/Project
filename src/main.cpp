#include <nlohmann/json.hpp>
#include <fstream>
#include "../include/Game.hpp"
#include "../include/Menu.hpp"
#include <iostream>
#include "../include/Resources/SaveData.hpp"

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    unsigned int screenWidth = desktop.width;
    unsigned int screenHeight = desktop.height;
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Fullscreen Window", sf::Style::Default);

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

    int typeOfBullet;

    // Load saved data
    loadSavedData(
        numberOfPlayers,
        player1Level, player1Hp, player1HpMax, player1Exp, player1ExpNext, player1Score,
        player2Level, player2Hp, player2HpMax, player2Exp, player2ExpNext, player2Score,
        upperWeapon, upperWeaponLevel,
        lowerWeapon, lowerWeaponLevel,
        typeOfBullet);

    Game* game= new Game(&window, numberOfPlayers,
              player1Level, player1Hp, player1HpMax, player1Exp, player1ExpNext, player1Score,
              player2Level, player2Hp, player2HpMax, player2Exp, player2ExpNext, player2Score,
              upperWeapon, upperWeaponLevel,
              lowerWeapon, lowerWeaponLevel,
              typeOfBullet);

    Menu* menu = new Menu(&window, game);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) && !game->isGameOver())
            {
                // Extract current game state before saving
                game->getGameState(numberOfPlayers,
                                  player1Level, player1Hp, player1HpMax, player1Exp, player1ExpNext, player1Score,
                                  player2Level, player2Hp, player2HpMax, player2Exp, player2ExpNext, player2Score,
                                  upperWeapon, upperWeaponLevel,
                                  lowerWeapon, lowerWeaponLevel);

                saveData(
                    numberOfPlayers,
                    player1Level, player1Hp, player1HpMax, player1Exp, player1ExpNext, player1Score,
                    player2Level, player2Hp, player2HpMax, player2Exp, player2ExpNext, player2Score,
                    upperWeapon, upperWeaponLevel,
                    lowerWeapon, lowerWeaponLevel,
                    0);

                window.close();
            }
        }

        // Update dt
        float dt = clock.restart().asSeconds();

        // Update
        if (!game->isInGame())
        {
            menu->update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)), event);
        }

        if (game->isInGame() && game->times++ < 1)
        {
            std::cout << "Loading saved data" << std::endl;
            loadSavedData(
                numberOfPlayers,
                player1Level, player1Hp, player1HpMax, player1Exp, player1ExpNext, player1Score,
                player2Level, player2Hp, player2HpMax, player2Exp, player2ExpNext, player2Score,
                upperWeapon, upperWeaponLevel,
                lowerWeapon, lowerWeaponLevel,
                typeOfBullet);
            game->loadSavedGameData(
                numberOfPlayers,
                player1Level, player1Hp, player1HpMax, player1Exp, player1ExpNext, player1Score,
                player2Level, player2Hp, player2HpMax, player2Exp, player2ExpNext, player2Score,
                upperWeapon, upperWeaponLevel,
                lowerWeapon, lowerWeaponLevel,
                typeOfBullet);
        }
        if (game->isInGame())
        {

            game->update(dt);
        }

        if (!game->isInGame())
        {
            menu->render(window);
        }
        else
        {
            game->render();
        }
    }

    return EXIT_SUCCESS;
}
