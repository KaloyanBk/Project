#include "../../include/Resources/Button.hpp"
#include <iostream>

Button::Button(float x, float y, float width, float height, sf::Font &font, const std::string &text,
               const sf::Color &idleColor, const sf::Color &hoverColor, const sf::Color &activeColor)
    : font(font), idleColor(idleColor), hoverColor(hoverColor), activeColor(activeColor), onClick(nullptr), buttonState(BTN_IDLE), wasPressed(false)
{
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));

    this->text.setFont(this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(24);
    this->text.setPosition(
        this->shape.getPosition().x + (this->shape.getSize().x / 2.f) - (this->text.getGlobalBounds().width / 2.f),
        this->shape.getPosition().y + (this->shape.getSize().y / 2.f) - (this->text.getGlobalBounds().height / 2.f));

    this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{
}

void Button::setOnClick(std::function<void()> func)
{
    this->onClick = func;
}

void Button::update(const sf::Vector2f &mousePos)
{
    // Previous button state
    bool wasHover = (this->buttonState == BTN_HOVER);
    bool wasActive = (this->buttonState == BTN_ACTIVE);

    // Current button state
    this->buttonState = BTN_IDLE;

    // Hover
    if (this->shape.getGlobalBounds().contains(mousePos))
    {
        this->buttonState = BTN_HOVER;

        // Pressed
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->buttonState = BTN_ACTIVE;
        }
        else
        {
            // Released
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
        // Released outside the button
        if (wasActive && this->onClick && !wasPressed)
        {
            wasPressed = true;
        }
    }

    // Reset wasPressed flag when the button is no longer active
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        wasPressed = false;
    }

    // Update button color based on state
    this->updateColor();
}

void Button::render(sf::RenderTarget &target)
{
    target.draw(this->shape);
    target.draw(this->text);
}

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
