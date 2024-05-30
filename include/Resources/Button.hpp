/**
 * @file Button.hpp
 * @author Klaoyan
 * @brief This is the header file for the Button class, which is used to create buttons for the game.
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <iostream>

class Button
{
public:
    Button(float x, float y, float width, float height, float radius, sf::Font &font, const std::string &text,
           const sf::Color &idleColor, const sf::Color &hoverColor, const sf::Color &activeColor);
    ~Button();

    void setOnClick(std::function<void()> func);
    inline bool isClicked(const sf::Vector2f &mousePos) const { return shape.getGlobalBounds().contains(mousePos); };
    inline const std::string getText() const { return text.getString(); }
    void update(const sf::Vector2f &mousePos);
    void render(sf::RenderTarget &target);
    void changeColor(const sf::Color &idleColor, const sf::Color &hoverColor, const sf::Color &activeColor)
    {
        this->idleColor = idleColor;
        this->hoverColor = hoverColor;
        this->activeColor = activeColor;
    };
    int timesPressed = 0;

private:
    sf::ConvexShape shape;
    sf::Font &font;
    sf::Text text;
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
    sf::Color changeColorTo;
    std::function<void()> onClick;

    enum ButtonState
    {
        BTN_IDLE,
        BTN_HOVER,
        BTN_ACTIVE
    };
    ButtonState buttonState;

    bool wasPressed = false;

    void updateColor();
    void setRoundedRectangle(sf::ConvexShape &shape, float width, float height, float radius);
};