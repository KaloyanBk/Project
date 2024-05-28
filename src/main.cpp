#include "../include/Game.hpp"
#include <iostream>

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

    int numberOfPlayers = 2;

    int player1Level = 1;
    int player1Hp = 8;
    int player1HpMax = 10;
    float player1Exp = 10.f;
    float player1ExpNext = 16.f;
    int player1Score = 0;

    int player2Level = 2;
    int player2Hp = 4;
    int player2HpMax = 16;
    float player2Exp = 10.f;
    float player2ExpNext = 16.f;
    int player2Score = 0;

    bool uperWeapon = true;
    int upperWeaponLevel = 2;

    bool lowerWeapon = true;
    int lowerWeaponLevel = 1;

    Game game(&window, numberOfPlayers,
              player1Level, player1Hp, player1HpMax, player1Exp, player1ExpNext, player1Score,
              player2Level, player2Hp, player2HpMax, player2Exp, player2ExpNext, player2Score,
              uperWeapon, upperWeaponLevel,
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
