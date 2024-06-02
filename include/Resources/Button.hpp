/**
 * @file Button.hpp
 * @author Klaoyan
 * 
 * @brief This is the header file for the Button class, which is used to create buttons for the game.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @details The Button class provides functionalities to create interactive buttons within the game,
 * including setting their position, size, colors for different states (idle, hover, active), and handling click events.
 * 
 * @note This file requires the SFML library.
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <iostream>

/**
 * @class Button
 * @brief A class to represent a button in the game.
 * 
 * This class encapsulates the properties and behaviors of a button, including rendering,
 * updating its state based on user interactions, and handling click events.
 */
class Button
{
public:
    /**
     * @brief Construct a new Button object.
     * 
     * @param x X coordinate of the button's position.
     * @param y Y coordinate of the button's position.
     * @param width Width of the button.
     * @param height Height of the button.
     * @param radius Radius for the button's corners.
     * @param font Font used for the button's text.
     * @param text Text displayed on the button.
     * @param idleColor Color of the button when idle.
     * @param hoverColor Color of the button when hovered.
     * @param activeColor Color of the button when active (pressed).
     */
    Button(float x, float y, float width, float height, float radius, sf::Font &font, const std::string &text,
           const sf::Color &idleColor, const sf::Color &hoverColor, const sf::Color &activeColor);

    ~Button();

    /**
     * @brief Set the callback function to be called when the button is clicked.
     * 
     * @param func A std::function object representing the callback function.
     */
    void setOnClick(std::function<void()> func);

    /**
     * @brief Check if the button is clicked based on the mouse position.
     * 
     * @param mousePos Position of the mouse cursor.
     * @return true If the button is clicked.
     * @return false If the button is not clicked.
     */
    inline bool isClicked(const sf::Vector2f &mousePos) const { return shape.getGlobalBounds().contains(mousePos); };

    /**
     * @brief Get the text displayed on the button.
     * 
     * @return The text displayed on the button as a std::string.
     */
    inline const std::string getText() const { return text.getString(); }

    /**
     * @brief Update the button's state based on the mouse position.
     * 
     * @param mousePos Position of the mouse cursor.
     */
    void update(const sf::Vector2f &mousePos);

    /**
     * @brief Render the button on the target.
     * 
     * @param target The render target to draw the button on.
     */
    void render(sf::RenderTarget &target);

    /**
     * @brief Change the button's colors for different states.
     * 
     * @param idleColor New idle color.
     * @param hoverColor New hover color.
     * @param activeColor New active color.
     */
    void changeColor(const sf::Color &idleColor, const sf::Color &hoverColor, const sf::Color &activeColor)
    {
        this->idleColor = idleColor;
        this->hoverColor = hoverColor;
        this->activeColor = activeColor;
    }

    int timesPressed = 0;

private:
    sf::ConvexShape shape; ///< Shape of the button.
    sf::Font &font; ///< Font used for the button's text.
    sf::Text text; ///< Text displayed on the button.
    sf::Color idleColor; ///< Color of the button when idle.
    sf::Color hoverColor; ///< Color of the button when hovered.
    sf::Color activeColor; ///< Color of the button when active (pressed).
    sf::Color changeColorTo; ///< Color to change the button to.
    std::function<void()> onClick; ///< Callback function to be called when the button is clicked.

    /**
     * @enum ButtonState
     * @brief Enumeration to represent the button's state.
     */
    enum ButtonState
    {
        BTN_IDLE, ///< Button is idle.
        BTN_HOVER, ///< Button is hovered.
        BTN_ACTIVE ///< Button is active (pressed).
    };
    ButtonState buttonState; ///< Current state of the button.

    bool wasPressed = false; ///< Flag to track if the button was previously pressed.

    /**
     * @brief Update the button's color based on its state.
     */
    void updateColor();

    /**
     * @brief Set the shape of the button to a rounded rectangle.
     * 
     * @param shape Shape to be set as a rounded rectangle.
     * @param width Width of the rounded rectangle.
     * @param height Height of the rounded rectangle.
     * @param radius Radius of the corners of the rounded rectangle.
     */
    void setRoundedRectangle(sf::ConvexShape &shape, float width, float height, float radius);
};
