/**
 * @file TextTag.cpp
 * @brief Implementation file for the TextTag class.
 * @author Kaloyan
 * @version 0.1
 * @date 2024-05-30
 * 
 * This file defines the member functions of the TextTag class, which is used to create text tags that can be displayed on the screen.
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "../include/TextTag.hpp"

/**
 * @brief Constructs a TextTag object.
 * 
 * @param font Pointer to the font used for the text tag.
 * @param text The string to be displayed as the text tag.
 * @param position The initial position of the text tag.
 * @param direction The direction in which the text tag moves.
 * @param size The character size of the text tag.
 * @param timerMax The maximum lifetime of the text tag.
 * @param accelerate Flag indicating whether the text tag should accelerate as it ages.
 * @param color The color of the text tag.
 */
TextTag::TextTag(Font* font, std::string text,
                 Vector2f position, Vector2f direction, unsigned int size,
                 float timerMax, bool accelerate,
                 Color color)
    : font(font), timerMax(timerMax),
      speed(2.f), direction(direction.x, direction.y),
      dtMultiplier(60.f)
{
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setCharacterSize(size);
    this->text.setFillColor(color);
    this->text.setPosition(position);

    this->timer = this->timerMax;

    this->accelerate = accelerate;
}

/**
 * @brief Copy constructor for TextTag.
 * 
 * @param other The TextTag object to be copied.
 */
TextTag::TextTag(const TextTag& other)
{
    this->text = other.text;
    this->font = other.font;
    this->timerMax = other.timerMax;
    this->timer = other.timer;
    this->speed = other.speed;
    this->direction = other.direction;
    this->dtMultiplier = other.dtMultiplier;
    this->accelerate = other.accelerate;
}

/**
 * @brief Assignment operator for TextTag.
 * 
 * @param other The TextTag object to be assigned.
 * @return Reference to the assigned TextTag object.
 */
TextTag& TextTag::operator=(const TextTag& other)
{
    if (this != &other)
    {
        this->text = other.text;
        this->font = other.font;
        this->timerMax = other.timerMax;
        this->timer = other.timer;
        this->speed = other.speed;
        this->direction = other.direction;
        this->dtMultiplier = other.dtMultiplier;
        this->accelerate = other.accelerate;
    }
    return *this;
}

/**
 * @brief Destructor for TextTag.
 */
TextTag::~TextTag()
{
}

/**
 * @brief Updates the state of the TextTag.
 * 
 * @param dt The change in time since the last update.
 */
void TextTag::Update(const float& dt)
{
    if (this->timer > 0.f)
    {
        this->timer -= 1.f * dt * this->dtMultiplier;
        if (this->accelerate)
        {
            if (this->timer > this->timerMax / 2.f)
            {
                this->text.move((this->speed * 5.f ) * this->direction.x * dt * this->dtMultiplier,
                                (this->speed * 5.f) * this->direction.y * dt * this->dtMultiplier);
            }
            else
            {
                this->text.move(this->speed * this->direction.x * dt * this->dtMultiplier,
                                this->speed * this->direction.y * dt * this->dtMultiplier);
            }
        }
        else
        {
            this->text.move(this->speed * this->direction.x * dt * this->dtMultiplier,
                            this->speed * this->direction.y * dt * this->dtMultiplier);
        }
    }
    else
    {
        this->text.setFillColor(Color(255, 255, 255, 0));
    }
}

/**
 * @brief Renders the TextTag on a render target.
 * 
 * @param target The render target on which to draw the TextTag.
 */
void TextTag::Render(RenderTarget& target)
{
    target.draw(this->text);
}
