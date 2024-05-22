#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;

class TextTag
{
private:
float dtMultiplier;

Font *font;
Text text;

float speed;
Vector2f direction;

float timerMax;
float timer;

public:
    TextTag(Font *font, std::string text, Vector2f position, unsigned int size, Color color);
    virtual ~TextTag();

    // Accessors
    inline const float &getTimer() const { return this->timer; }

    void Update(const float &dt);
    void Render(RenderTarget &target);
};

