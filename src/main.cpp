/**
 * @file main.cpp
 * @author Kaloyan
 * @brief This is the main file for the game.
 * @details This file contains the main function which initializes the game window, loads saved data, creates game and menu objects, and starts the main game loop.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

#include "../include/Game.hpp"
#include "../include/Menu.hpp"
#include "../include/Resources/SaveData.hpp"

int main()
{
    /// Seed the random number generator
    srand(static_cast<unsigned>(time(nullptr)));

    /// Create a fullscreen window
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    unsigned int screenWidth = desktop.width;
    unsigned int screenHeight = desktop.height;
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Fullscreen Window", sf::Style::Fullscreen);

    if (!window.isOpen())
    {
        /// Handle window creation failure
        std::cerr << "Failed to create window!" << std::endl;
        return EXIT_FAILURE;
    }

    sf::Clock clock;

    /// Load saved data
    int numberOfPlayers;
    /// Player 1 data
    int player1Level;
    int player1Hp;
    int player1HpMax;
    float player1Exp;
    float player1ExpNext;
    int player1Score;
    /// Player 2 data
    int player2Level;
    int player2Hp;
    int player2HpMax;
    float player2Exp;
    float player2ExpNext;
    int player2Score;
    /// Weapons data
    bool upperWeapon;
    int upperWeaponLevel;
    bool lowerWeapon;
    int lowerWeaponLevel;
    int typeOfBullet;
    loadSavedData(
        numberOfPlayers,
        player1Level, player1Hp, player1HpMax, player1Exp, player1ExpNext, player1Score,
        player2Level, player2Hp, player2HpMax, player2Exp, player2ExpNext, player2Score,
        upperWeapon, upperWeaponLevel,
        lowerWeapon, lowerWeaponLevel,
        typeOfBullet);

    /// Create the game object
    Game* game= new Game(&window, numberOfPlayers,
              player1Level, player1Hp, player1HpMax, player1Exp, player1ExpNext, player1Score,
              player2Level, player2Hp, player2HpMax, player2Exp, player2ExpNext, player2Score,
              upperWeapon, upperWeaponLevel,
              lowerWeapon, lowerWeaponLevel,
              typeOfBullet);

    /// Create the menu object
    Menu* menu = new Menu(&window, game);

    /// Main game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) && !game->isGameOver())
            {
                /// Extract current game state before saving
                game->getGameState(numberOfPlayers,
                                  player1Level, player1Hp, player1HpMax, player1Exp, player1ExpNext, player1Score,
                                  player2Level, player2Hp, player2HpMax, player2Exp, player2ExpNext, player2Score,
                                  upperWeapon, upperWeaponLevel,
                                  lowerWeapon, lowerWeaponLevel);

                /// Save current game state
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

        /// Update dt
        float dt = clock.restart().asSeconds();

        /// Update
        /// Handle menu input
        if (!game->isInGame())
        {
            menu->update(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)), event);
        }

        /// Handle game input
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

        /// Update the game
        if (game->isInGame())
        {
            game->update(dt);
        }

        /// Render
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