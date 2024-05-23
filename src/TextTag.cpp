#include "../include/TextTag.hpp"

TextTag::TextTag(Font *font, std::string text, Vector2f position, unsigned int size, float timerMax, Color color)
    : font(font), timerMax(timerMax), timer(timerMax), speed(4.f), direction(0.f, -1.f), dtMultiplier(60.f) {
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setCharacterSize(size);
    this->text.setFillColor(color);
    this->text.setPosition(position);
}

TextTag::TextTag(const TextTag& other)
    : text(other.text), font(other.font), timerMax(other.timerMax), timer(other.timer),
      speed(other.speed), direction(other.direction), dtMultiplier(other.dtMultiplier) {
}

TextTag& TextTag::operator=(const TextTag& other) {
    if (this != &other) {
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

TextTag::~TextTag() {
    // Any necessary cleanup
}

void TextTag::Update(const float &dt) {
    if (this->timer > 0.f) {
        this->timer -= 1.f * dt * this->dtMultiplier;
        this->text.move(this->speed * this->direction.x * dt * this->dtMultiplier,
                        this->speed * this->direction.y * dt * this->dtMultiplier);
    } else {
        this->text.setFillColor(Color(255, 255, 255, 0));
    }
}

void TextTag::Render(RenderTarget &target) {
    target.draw(this->text);
}
