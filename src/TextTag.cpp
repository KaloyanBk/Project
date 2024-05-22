#include "../include/TextTag.hpp"

TextTag::TextTag(Font *font, std::string text, Vector2f position, unsigned int size, Color color):
    dtMultiplier(60.f),
    font(font),
    timerMax(10.f),timer(timerMax),
    speed(5.f),direction(0.f,-1.f)
{
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setCharacterSize(size);
    this->text.setFillColor(color);
    this->text.setPosition(position);
}

TextTag::~TextTag()
{
}

void TextTag::Update(const float &dt)
{
    if (this->timer > 0.f)
    {
        this->timer -= 1.f * dt * this->dtMultiplier;
        this->text.move(this->speed * this->direction.x * dt * this->dtMultiplier,
                        this->speed * this->direction.y * dt * this->dtMultiplier);
    }else
    {
        this->text.setFillColor(Color(255, 255, 255, 0));
    }
}

void TextTag::Render(RenderTarget &target)
{
    target.draw(this->text);
}
