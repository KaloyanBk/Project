
#include "../include/Menu.hpp"
#include <iostream>

// Constructor
Menu::Menu(sf::RenderWindow *window, Game *game)
    : window(window), active(true), game(game)
{
    if (!font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        std::cerr << "Failed to load font" << std::endl;
    }

    title.setFont(font);
    title.setString("Main Menu");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::White);
    title.setPosition(window->getSize().x / 2.f - title.getGlobalBounds().width / 2.f, 50.f);

    // Add Start button
    addButton(100.f, 200.f, 150.f, 50.f, font, "Start");
    addButton(300.f, 200.f, 150.f, 50.f, font, "Laser");
    addButton(500.f, 200.f, 150.f, 50.f, font, "Lightning");
    addButton(700.f, 200.f, 150.f, 50.f, font, "Dark Matter");
    addButton(300.f, 300.f, 150.f, 50.f, font, "Nuclier Material");
    addButton(500.f, 300.f, 150.f, 50.f, font, "Plasma");
    addButton(700.f, 300.f, 150.f, 50.f, font, "Planetary Bomb");
    addButton(300.f, 400.f, 150.f, 50.f, font, "Upper Weapon");
    addButton(500.f, 400.f, 150.f, 50.f, font, "Level 1");
    addButton(700.f, 400.f, 150.f, 50.f, font, "Level 2");
    addButton(900.f, 400.f, 150.f, 50.f, font, "Level 3");
    addButton(300.f, 500.f, 150.f, 50.f, font, "Lower Weapon");
    addButton(500.f, 500.f, 150.f, 50.f, font, "Level 1 ");
    addButton(700.f, 500.f, 150.f, 50.f, font, "Level 2 ");
    addButton(900.f, 500.f, 150.f, 50.f, font, "Level 3 ");
}

void Menu::render(sf::RenderTarget &target)
{
    this->window->clear();
    target.draw(title);
    for (auto &button : buttons)
    {
        button.render(target);
    }
    this->window->display();
}
void Menu::resetColor()
{
    for (auto &button : buttons)
    {
        if (button.getText() == "Laser" || button.getText() == "Lightning" || button.getText() == "Dark Matter" || button.getText() == "Nuclier Material" || button.getText() == "Plasma" || button.getText() == "Planetary Bomb")
        {
            button.changeColor(sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
        }
    }
}
void Menu::resetUpperLevelColor()
{
    for (auto &button : buttons)
    {
        if (button.getText() == "Level 1" || button.getText() == "Level 2" || button.getText() == "Level 3")
        {
            button.changeColor(sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
        }
    }
}
void Menu::resetLowerLevelColor()
{
    for (auto &button : buttons)
    {
        if (button.getText() == "Level 1 " || button.getText() == "Level 2 " || button.getText() == "Level 3 ")
        {
            button.changeColor(sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
        }
    }
}

void Menu::update(const sf::Vector2f &mousePos, sf::Event &event)
{
    if (game->hasBeenReset())
    {
        resetColor();
        resetUpperLevelColor();
        resetLowerLevelColor();
        game->reseted(false);
    }
    
    for (auto &button : buttons)
    {
        button.update(mousePos);

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if (button.isClicked(mousePos))
            {
                if (button.getText() == "Start")
                {

                    game->setIsGameStarted(true);
                }
                else if (button.getText() == "Laser")
                {
                    resetColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));

                    game->setWeaponType(0);
                }
                else if (button.getText() == "Lightning")
                {
                    resetColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));

                    game->setWeaponType(1);
                }
                else if (button.getText() == "Dark Matter")
                {
                    resetColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));

                    game->setWeaponType(2);
                }
                else if (button.getText() == "Nuclier Material")
                {
                    resetColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));

                    game->setWeaponType(3);
                }
                else if (button.getText() == "Plasma")
                {
                    resetColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));

                    game->setWeaponType(4);
                }
                else if (button.getText() == "Planetary Bomb")
                {
                    resetColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    game->setWeaponType(5);
                }
                else if (button.getText() == "Upper Weapon")
                {
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    game->setUpperWeapon(true);
                }
                else if (button.getText() == "Level 1")
                {
                    resetUpperLevelColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    game->setUpperWeaponLevel(0);
                }
                else if (button.getText() == "Level 2")
                {
                    resetUpperLevelColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    game->setUpperWeaponLevel(1);
                }
                else if (button.getText() == "Level 3")
                {
                    resetUpperLevelColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    game->setUpperWeaponLevel(2);
                }
                else if (button.getText() == "Lower Weapon")
                {
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    game->setLowerWeapon(true);
                }
                else if (button.getText() == "Level 1 ")
                {
                    resetLowerLevelColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    game->setLowerWeaponLevel(0);
                }
                else if (button.getText() == "Level 2 ")
                {
                    resetLowerLevelColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    game->setLowerWeaponLevel(1);
                }
                else if (button.getText() == "Level 3 ")
                {
                    resetLowerLevelColor();
                    button.changeColor(sf::Color(31, 102, 17, 200), sf::Color(117, 153, 110, 200), sf::Color(20, 20, 20, 200));
                    game->setLowerWeaponLevel(2);
                }
            }
        }
    }
}

void Menu::addButton(float x, float y, float width, float height, sf::Font &font, const std::string &text)
{
    buttons.emplace_back(x, y, width, height, font, text,
                         sf::Color(70, 70, 70, 200),
                         sf::Color(150, 150, 150, 200),
                         sf::Color(20, 20, 20, 200));
}

bool Menu::isButtonPressed(int index)
{
    if (index >= 0 && index < buttons.size())
    {
        return buttons[index].isClicked(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window)));
    }
    return false;
}
