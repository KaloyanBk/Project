#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "./Resources/Button.hpp"
#include "TextTag.hpp"
#include "Game.hpp"

class Menu
{
private:
    Game *game;
    sf::RenderWindow *window;
    sf::Font font;
    sf::Text title;
    std::vector<Button> buttons;
    bool active;

public:
    Menu(sf::RenderWindow *window, Game *game);
    void render(sf::RenderTarget &target);
    void update(const sf::Vector2f &mousePos, sf::Event &event);
    void addButton(float x, float y, float width, float height, sf::Font &font, const std::string &text);
    void resetColor();
    void resetUpperLevelColor();
    void resetLowerLevelColor();

    bool isButtonPressed(int index);
};
