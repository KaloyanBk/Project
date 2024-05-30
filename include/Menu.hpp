/**
 * @file Menu.hpp
 * @author Kaloyan
 * @brief This is the header file for the Menu class, which is used to create the main menu of the game.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "./Resources/Button.hpp"
#include "TextTag.hpp"
#include "Game.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Menu
{
private:
    Game *game;
    sf::RenderWindow *window;
    sf::Font font;
    sf::Text title;
    sf::Text continueText;
    std::vector<Button> buttons;
    std::vector<Button> beginMenuButtons;
    bool active;
    bool newGame;
    bool beginMenu;

    int numberOfPlayers;
    int player1Level;
    int player2Level;
    int upperWeaponLevel;
    int lowerWeaponLevel;
    bool upperWeapon;
    bool lowerWeapon;
    float player1Exp;
    float player2Exp;
    float player1ExpNext;
    float player2ExpNext;
    int player1Hp;
    int player2Hp;
    int player1HpMax;
    int player2HpMax;
    int player1Score;
    int player2Score;

    int typeOfBullet;

public:
    Menu(sf::RenderWindow *window, Game *game);
    void render(sf::RenderTarget &target);
    void update(const sf::Vector2f &mousePos, sf::Event &event);
    void addButton(float x, float y, float width, float height, float cornerRadius, sf::Font &font, const std::string &text);
    void addButtonToBeginMenu(float x, float y, float width, float height, float cornerRadius, sf::Font &font, const std::string &text);
    void resetColor();
    void resetUpperLevelColor();
    void resetLowerLevelColor();
    void resetAllColor();
    void setNewGame(bool newGame)
    {
        this->newGame = newGame;
        this->beginMenu = false;
    };

    bool isButtonPressed(int index) const;
};
