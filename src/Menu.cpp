/**
 * @file Menu.cpp
 * @author Kaloyan
 * @brief This is the implementation file for the Menu class, which is used to create and manage the game menu.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "../include/Menu.hpp"
#include <iostream>
#include <fstream>

/**
 * @brief Construct a new Menu::Menu object
 * 
 * @param window Pointer to the SFML RenderWindow
 * @param game Pointer to the Game object
 */
Menu::Menu(sf::RenderWindow *window, Game *game)
    : window(window), game(game), active(true), newGame(false), beginMenu(true)
{
    /// Load font for menu text
    if (!font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        std::cerr << "Failed to load font" << std::endl;
    }

    /// Set up title text for the menu
    title.setFont(font);
    title.setString("Main Menu");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::White);
    title.setPosition(window->getSize().x / 2.f - title.getGlobalBounds().width / 2.f, 50.f);

    float cornerRadius = 10.0f;

    /// Add buttons to the beginning menu
    addButtonToBeginMenu(window->getSize().x / 2.f - 100.f, window->getSize().y / 2.f + 50.f, 150.f, 50.f, cornerRadius, font, "Continue");
    addButtonToBeginMenu(window->getSize().x / 2.f + 100.f, window->getSize().y / 2.f + 50.f, 150.f, 50.f, cornerRadius, font, "New Game");

    /// Add buttons to the main menu
    addButton(100.f, 200.f, 150.f, 50.f, cornerRadius, font, "Start");
    addButton(300.f, 200.f, 150.f, 50.f, cornerRadius, font, "Laser");
    addButton(500.f, 200.f, 150.f, 50.f, cornerRadius, font, "Lightning");
    addButton(700.f, 200.f, 150.f, 50.f, cornerRadius, font, "Dark Matter");
    addButton(300.f, 300.f, 150.f, 50.f, cornerRadius, font, "Nuclier Material");
    addButton(500.f, 300.f, 150.f, 50.f, cornerRadius, font, "Plasma");
    addButton(700.f, 300.f, 150.f, 50.f, cornerRadius, font, "Planetary Bomb");
    addButton(300.f, 400.f, 150.f, 50.f, cornerRadius, font, "Upper Weapon");
    addButton(500.f, 400.f, 150.f, 50.f, cornerRadius, font, "Level 1");
    addButton(700.f, 400.f, 150.f, 50.f, cornerRadius, font, "Level 2");
    addButton(900.f, 400.f, 150.f, 50.f, cornerRadius, font, "Level 3");
    addButton(300.f, 500.f, 150.f, 50.f, cornerRadius, font, "Lower Weapon");
    addButton(500.f, 500.f, 150.f, 50.f, cornerRadius, font, "Level 1 ");
    addButton(700.f, 500.f, 150.f, 50.f, cornerRadius, font, "Level 2 ");
    addButton(900.f, 500.f, 150.f, 50.f, cornerRadius, font, "Level 3 ");

    addButton(100.f, 600.f, 150.f, 50.f, cornerRadius, font, "2 Players");
}

/**
 * @brief Render the menu on the given render target
 * 
 * @param target Render target to draw on
 */
void Menu::render(sf::RenderTarget &target)
{
    /// Clear the window
    if (window == nullptr)
    {
        std::cerr << "Error: Window pointer is null!" << std::endl;
        return;
    }
    window->clear();

    /// Render the appropriate menu based on the state
    if (beginMenu)
    {
        /// Render buttons for the beginning menu
        for (auto &button : beginMenuButtons)
        {
            button.render(target);
        }
    }
    else
    {
        /// Render title and buttons for the main menu
        target.draw(title);
        for (auto &button : buttons)
        {
            button.render(target);
        }
    }

    /// Display the window
    window->display();
}

/**
 * @brief Reset color for all buttons
 */
void Menu::resetAllColor()
{
    /// Reset color for all buttons
    for (auto &button : buttons)
    {
        button.changeColor(sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
    }
}

/**
 * @brief Reset color for specific buttons related to weapon types
 */
void Menu::resetColor()
{
    /// Reset color for specific buttons
    for (auto &button : buttons)
    {
        if (button.getText() == "Laser" || button.getText() == "Lightning" || button.getText() == "Dark Matter" ||
            button.getText() == "Nuclier Material" || button.getText() == "Plasma" || button.getText() == "Planetary Bomb")
        {
            button.changeColor(sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
        }
    }
}

/**
 * @brief Reset color for upper level buttons
 */
void Menu::resetUpperLevelColor()
{
    /// Reset color for upper level buttons
    for (auto &button : buttons)
    {
        if (button.getText() == "Level 1" || button.getText() == "Level 2" || button.getText() == "Level 3")
        {
            button.changeColor(sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
        }
    }
}

/**
 * @brief Reset color for lower level buttons
 */
void Menu::resetLowerLevelColor()
{
    /// Reset color for lower level buttons
    for (auto &button : buttons)
    {
        if (button.getText() == "Level 1 " || button.getText() == "Level 2 " || button.getText() == "Level 3 ")
        {
            button.changeColor(sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
        }
    }
}

/**
 * @brief Update the menu based on mouse position and events
 * 
 * @param mousePos Position of the mouse cursor
 * @param event SFML event to process
 */
void Menu::update(const sf::Vector2f &mousePos, sf::Event &event)
{
    if (game->hasBeenReset())
    {
        this->resetAllColor();
        this->setNewGame(true);
        game->reseted(false);
    }
    for (auto &button : beginMenuButtons)
    {
        button.update(mousePos);
        if (button.isClicked(mousePos) && event.type == sf::Event::MouseButtonReleased)
        {
            if (button.getText() == "New Game")
            {
                eraceSavedData();
                newGame = true;
                beginMenu = false;
            }
            else if (button.getText() == "Continue")
            {
                newGame = false;
                beginMenu = false;
                game->setIsGameStarted(true);
            }
        }
    }
    if (newGame)
    {
        for (auto &button : buttons)
        {
            button.update(mousePos);

            if (button.isClicked(mousePos) && event.type == sf::Event::MouseButtonReleased)
            {

                if (button.getText() == "Start")
                {
                    game->setIsGameStarted(true);
                }
                else if (button.getText() == "Laser")
                {
                    resetColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    setTypeOfBullet(0);
                }
                else if (button.getText() == "Lightning")
                {
                    resetColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    setTypeOfBullet(1);
                }
                else if (button.getText() == "Dark Matter")
                {
                    resetColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    setTypeOfBullet(2);
                }
                else if (button.getText() == "Nuclier Material")
                {
                    resetColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    setTypeOfBullet(3);
                }
                else if (button.getText() == "Plasma")
                {
                    resetColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    setTypeOfBullet(4);
                }
                else if (button.getText() == "Planetary Bomb")
                {
                    resetColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    setTypeOfBullet(5);
                }
                else if (button.getText() == "Upper Weapon")
                {
                    if (button.timesPressed % 2 == 0)
                    {
                        button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                        setUpperWeapon(true);
                    }
                    else
                    {
                        button.changeColor(sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
                        setUpperWeapon(false);
                    }
                }
                else if (button.getText() == "Level 1")
                {
                    resetUpperLevelColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    setUpperWeaponLevel(0);
                }
                else if (button.getText() == "Level 2")
                {
                    resetUpperLevelColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    setUpperWeaponLevel(1);
                }
                else if (button.getText() == "Level 3")
                {
                    resetUpperLevelColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    setUpperWeaponLevel(2);
                }
                else if (button.getText() == "Lower Weapon")
                {
                    if (button.timesPressed % 2 == 0)
                    {
                        button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                        setLowerWeapon(true);
                    }
                    else
                    {
                        button.changeColor(sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
                        setLowerWeapon(false);
                    }
                }
                else if (button.getText() == "Level 1 ")
                {
                    resetLowerLevelColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    setLowerWeaponLevel(0);
                }
                else if (button.getText() == "Level 2 ")
                {
                    resetLowerLevelColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    setLowerWeaponLevel(1);
                }
                else if (button.getText() == "Level 3 ")
                {
                    resetLowerLevelColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    setLowerWeaponLevel(2);
                }
                else if (button.getText() == "2 Players")
                {
                    if (button.timesPressed % 2 == 0)
                    {
                        button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                        setNumberOfPlayers(2);
                    }
                    else
                    {
                        button.changeColor(sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
                        setNumberOfPlayers(1);
                    }
                }
            }
        }
    }
}

/**
 * @brief Add a button to the main menu
 * 
 * @param x X position of the button
 * @param y Y position of the button
 * @param width Width of the button
 * @param height Height of the button
 * @param cornerRadius Corner radius of the button
 * @param font Font used for the button text
 * @param text Text displayed on the button
 */
void Menu::addButton(float x, float y, float width, float height, float cornerRadius, sf::Font &font, const std::string &text)
{
    buttons.emplace_back(x, y, width, height, cornerRadius, font, text,
                                sf::Color(70, 70, 70, 200), 
                                sf::Color(150, 150, 150, 200),
                                sf::Color(20, 20, 20, 200));
}

/**
 * @brief Add a button to the beginning menu
 * 
 * @param x X position of the button
 * @param y Y position of the button
 * @param width Width of the button
 * @param height Height of the button
 * @param cornerRadius Corner radius of the button
 * @param font Font used for the button text
 * @param text Text displayed on the button
 */
void Menu::addButtonToBeginMenu(float x, float y, float width, float height, float cornerRadius, sf::Font &font, const std::string &text)
{
    beginMenuButtons.emplace_back(x, y, width, height, cornerRadius, font, text,
                                  sf::Color(70, 70, 70, 200),
                                  sf::Color(150, 150, 150, 200),
                                  sf::Color(20, 20, 20, 200));
}

/**
 * @brief Check if a button at the given index is pressed
 * 
 * @param index Index of the button
 * @return true if the button is pressed, false otherwise
 */
bool Menu::isButtonPressed(int index) const
{
    if (index >= 0 && index < buttons.size())
    {
        return buttons[index].isClicked(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window)));
    }
    return false;
}
