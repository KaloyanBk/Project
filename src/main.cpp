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

    /// Create fullscreen window
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Alien Invasion", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(true);
    window.requestFocus();

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

    /// Start in menu; game begins when menu sets isInGame

    /// Input state (event-driven)
    bool p1Up=false, p1Down=false, p1Left=false, p1Right=false, p1Fire=false;
    bool p2Up=false, p2Down=false, p2Left=false, p2Right=false, p2Fire=false;

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
                int bulletTypeToSave = typeOfBullet;
                if (game->isInGame())
                {
                    bulletTypeToSave = game->getBulletType();
                }
                saveData(
                    numberOfPlayers,
                    player1Level, player1Hp, player1HpMax, player1Exp, player1ExpNext, player1Score,
                    player2Level, player2Hp, player2HpMax, player2Exp, player2ExpNext, player2Score,
                    upperWeapon, upperWeaponLevel,
                    lowerWeapon, lowerWeaponLevel,
                    bulletTypeToSave);

                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::W) p1Up = true;
                if (event.key.code == sf::Keyboard::S) p1Down = true;
                if (event.key.code == sf::Keyboard::A) p1Left = true;
                if (event.key.code == sf::Keyboard::D) p1Right = true;
                if (event.key.code == sf::Keyboard::Space) p1Fire = true;

                if (event.key.code == sf::Keyboard::Up) p2Up = true;
                if (event.key.code == sf::Keyboard::Down) p2Down = true;
                if (event.key.code == sf::Keyboard::Left) p2Left = true;
                if (event.key.code == sf::Keyboard::Right) p2Right = true;
                if (event.key.code == sf::Keyboard::RShift) p2Fire = true;
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::W) p1Up = false;
                if (event.key.code == sf::Keyboard::S) p1Down = false;
                if (event.key.code == sf::Keyboard::A) p1Left = false;
                if (event.key.code == sf::Keyboard::D) p1Right = false;
                if (event.key.code == sf::Keyboard::Space) p1Fire = false;

                if (event.key.code == sf::Keyboard::Up) p2Up = false;
                if (event.key.code == sf::Keyboard::Down) p2Down = false;
                if (event.key.code == sf::Keyboard::Left) p2Left = false;
                if (event.key.code == sf::Keyboard::Right) p2Right = false;
                if (event.key.code == sf::Keyboard::RShift) p2Fire = false;
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
        // Feed input only during gameplay
        if (game->isInGame())
        {
            game->setInputState(0, p1Up, p1Down, p1Left, p1Right, p1Fire);
            if (numberOfPlayers == 2)
            {
                game->setInputState(1, p2Up, p2Down, p2Left, p2Right, p2Fire);
            }
            game->render();
        }
        else
        {
            menu->render(window);
        }
    }

    return EXIT_SUCCESS;
}