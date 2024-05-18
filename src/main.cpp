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

    Game game(&window);

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
