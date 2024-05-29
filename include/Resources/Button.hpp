#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <iostream>

class Button
{
public:
    Button(float x, float y, float width, float height, sf::Font &font, const std::string &text,
           const sf::Color &idleColor, const sf::Color &hoverColor, const sf::Color &activeColor);
    ~Button();

    void setOnClick(std::function<void()> func);
    inline bool isClicked(const sf::Vector2f &mousePos) const
    {
        return shape.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
    }
    inline const std::string getText() const { return text.getString(); }
    void update(const sf::Vector2f &mousePos);
    void render(sf::RenderTarget &target);
    void changeColor(const sf::Color &idleColor, const sf::Color &hoverColor, const sf::Color &activeColor)
    {
        this->idleColor = idleColor;
        this->hoverColor = hoverColor;
        this->activeColor = activeColor;
    };

private:
    sf::RectangleShape shape;
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
};
