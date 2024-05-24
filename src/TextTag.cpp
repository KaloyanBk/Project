#include "../include/TextTag.hpp"

TextTag::TextTag(Font *font, std::string text,
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

TextTag::TextTag(const TextTag &other)
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

TextTag &TextTag::operator=(const TextTag &other)
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
    }
    return *this;
}

TextTag::~TextTag()
{
    // Any necessary cleanup
}

void TextTag::Update(const float &dt)
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

void TextTag::Render(RenderTarget &target)
{
    target.draw(this->text);
}
