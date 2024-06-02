/**
 * @file Button.cpp
 * @author Kaloyan
 * @brief This is the implementation file for the Button class, which is used to create buttons for the game.
 * @version 0.1
 * @date 2024-05-30
 *
 * This file provides the implementation of the Button class, which allows creating interactive buttons in the game.
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "../../include/Resources/Button.hpp"
#include <iostream>

/**
 * @brief Constructs a Button object.
 *
 * Initializes the Button object with specified parameters.
 *
 * @param x The x-coordinate of the button position.
 * @param y The y-coordinate of the button position.
 * @param width The width of the button.
 * @param height The height of the button.
 * @param radius The corner radius of the button.
 * @param font Reference to the font used for the button text.
 * @param text The text displayed on the button.
 * @param idleColor The color of the button in idle state.
 * @param hoverColor The color of the button when hovered over.
 * @param activeColor The color of the button when clicked.
 */
Button::Button(float x, float y, float width, float height, float radius, sf::Font &font, const std::string &text,
               const sf::Color &idleColor, const sf::Color &hoverColor, const sf::Color &activeColor)
    : font(font), idleColor(idleColor), hoverColor(hoverColor), activeColor(activeColor), onClick(nullptr), buttonState(BTN_IDLE), wasPressed(false)
{
    this->shape.setPosition(sf::Vector2f(x, y));
    setRoundedRectangle(this->shape, width, height, radius);

    this->text.setFont(this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(24);

    /// Adjust the vertical offset by changing the Y position of the text
    float verticalOffset = -5.0f; 
    this->text.setPosition(
        this->shape.getPosition().x + (width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
        this->shape.getPosition().y + (height / 2.f) - (this->text.getGlobalBounds().height / 2.f) + verticalOffset);

    this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{
}

/**
 * @brief Sets the function to execute when the button is clicked.
 *
 * @param func The function to execute when the button is clicked.
 */
void Button::setOnClick(std::function<void()> func)
{
    this->onClick = func;
}

/**
 * @brief Updates the state of the button.
 *
 * Checks if the button is hovered over or clicked, and updates its state accordingly.
 *
 * @param mousePos The position of the mouse cursor.
 */
void Button::update(const sf::Vector2f &mousePos)
{
    bool wasHover = (this->buttonState == BTN_HOVER);
    bool wasActive = (this->buttonState == BTN_ACTIVE);

    this->buttonState = BTN_IDLE;

    if (this->shape.getGlobalBounds().contains(mousePos))
    {
        this->buttonState = BTN_HOVER;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->buttonState = BTN_ACTIVE;
        }
        else
        {
            if (wasActive && this->onClick && !wasPressed)
            {
                this->onClick();
                wasPressed = true;
            }
            if (wasActive && !wasPressed)
            {
                this->timesPressed++;
                wasPressed = true;
            }
        }
    }
    else
    {
        if (wasActive && this->onClick && !wasPressed)
        {
            wasPressed = true;
        }
    }

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        wasPressed = false;
    }

    this->updateColor();
}

/**
 * @brief Renders the button.
 *
 * Draws the button shape and text to the specified render target.
 *
 * @param target The render target to draw the button on.
 */
void Button::render(sf::RenderTarget &target)
{
    target.draw(this->shape);
    target.draw(this->text);
}

/**
 * @brief Updates the color of the button based on its state.
 *
 * Sets the fill color of the button shape according to its current state.
 */
void Button::updateColor()
{
    switch (this->buttonState)
    {
    case BTN_IDLE:
        this->shape.setFillColor(this->idleColor);
        break;
    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        break;
    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        break;
    }
}

/**
 * @brief Sets the shape of the button to a rounded rectangle.
 *
 * This function sets the shape of the button to a rounded rectangle with the specified width, height, and corner radius.
 *
 * @param shape The convex shape to be modified into a rounded rectangle.
 * @param width The width of the rounded rectangle.
 * @param height The height of the rounded rectangle.
 * @param radius The radius of the rounded corners.
 */
void Button::setRoundedRectangle(sf::ConvexShape &shape, float width, float height, float radius)
{
    const int pointsPerCorner = 10;
    const int totalPoints = pointsPerCorner * 4;

    shape.setPointCount(totalPoints);

    for (int i = 0; i < pointsPerCorner; ++i)
    {
        float angle = i * M_PI / 2.0 / (pointsPerCorner - 1);

        /// Top-left corner
        shape.setPoint(i, sf::Vector2f(radius * (1 - cos(angle)), radius * (1 - sin(angle))));

        /// Top-right corner
        shape.setPoint(pointsPerCorner + i, sf::Vector2f(width - radius + radius * sin(angle), radius * (1 - cos(angle))));

        /// Bottom-right corner
        shape.setPoint(2 * pointsPerCorner + i, sf::Vector2f(width - radius + radius * cos(angle), height - radius + radius * sin(angle)));

        /// Bottom-left corner
        shape.setPoint(3 * pointsPerCorner + i, sf::Vector2f(radius * (1 - sin(angle)), height - radius + radius * cos(angle)));
    }
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::Black);
}

//  void Button::setRoundedRectangle(sf::ConvexShape &shape, float width, float height, float radius)
//  {
//      const int pointsPerCorner = 10;
//      const int totalPoints = pointsPerCorner * 4;

//     shape.setPointCount(totalPoints);

//      for (int i = 0; i < pointsPerCorner; ++i)
//     {
//          float angle = i * M_PI / 2.0 / (pointsPerCorner - 1);

//          /// Top-left corner
//          shape.setPoint(i, sf::Vector2f(radius * (1 - cos(angle)), radius * (1 - sin(angle))));

//          /// Top-right corner
//          shape.setPoint(pointsPerCorner + i, sf::Vector2f(width - radius + radius * cos(angle), radius * (1 - sin(angle))));

//          /// Bottom-right corner
//          shape.setPoint(2 * pointsPerCorner + i, sf::Vector2f(width - radius + radius * cos(angle), height - radius + radius * sin(angle)));

//          /// Bottom-left corner
//          shape.setPoint(3 * pointsPerCorner + i, sf::Vector2f(radius * (1 - cos(angle)), height - radius + radius * sin(angle)));
//      }

//      shape.setOutlineThickness(1);
//     shape.setOutlineColor(sf::Color::Black);
//  }
