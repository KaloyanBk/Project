// Game.cpp

#include "../include/Game.hpp"
#include "../include/Weapons/PeaShooter.hpp"
#include <iostream>

Game::Game(RenderWindow *window) : window(window)
{
    // Window
    this->window->setFramerateLimit(60);

    // Load resources
    this->loadResources();

    // Textures
    this->loadTextures();

    // Players
    this->createPlayers();

    // Enemy
    this->enemySpawnTimerMax = 20;
    this->enemySpawnTimer = this->enemySpawnTimerMax;

    // UI
    this->InItUi();
}

Game::~Game()
{
    for (auto &p : players)
    {
        delete p;
    }

    for (auto &e : enemys)
    {
        delete e;
    }
}

void Game::loadTextures()
{
    for (size_t i = 0; i < NUM_RESOURCES; ++i)
    {
        Texture texture;
        if (!texture.loadFromFile(resourcePaths.at(static_cast<Textures>(i))))
        {
            std::cerr << "Failed to load texture: " << resourcePaths.at(static_cast<Textures>(i)) << std::endl;
        }
        this->textures.push_back(texture);
    }
}

void Game::loadResources()
{
    if (!font.loadFromFile(resourcePathsFonts.at(DOSIS_LIGHT)))
    {
        std::cerr << "Failed to load font: " << resourcePathsFonts.at(DOSIS_LIGHT) << std::endl;
    }
}

void Game::createPlayers()
{
    this->players.push_back(new Player(this->textures, this->window->getSize()));
    // this->players.push_back(createPlayer(this->textures, this->window->getSize(), Keyboard::Up, Keyboard::Down, Keyboard::Left, Keyboard::Right, Keyboard::RShift));
}

Player *Game::createPlayer(std::vector<Texture> &textures, Vector2u windowBounds,
                           int upKey, int downKey, int leftKey, int rightKey, int fireKey)
{
    return new Player(textures, windowBounds, upKey, downKey, leftKey, rightKey, fireKey);
}

void Game::InItUi()
{
    // Follow Player Text
    Text ftext;
    for (size_t i = 0; i < players.size(); i++)
    {
        ftext.setFont(font);
        ftext.setCharacterSize(24);
        ftext.setFillColor(Color::White);
        ftext.setString("Player: " + std::to_string(i + 1));

        this->followPlayerTexts.push_back(ftext);

        // Stationary Text
        Text sText;
        sText.setFont(font);
        sText.setCharacterSize(12);
        sText.setFillColor(Color::White);
        sText.setString("");

        this->stationaryTexts.push_back(sText);
    }
}

void Game::UpdateUI()
{
    for (size_t i = 0; i < players.size(); i++)
    {
        this->followPlayerTexts[i].setPosition(
            this->players[i]->getPosition().x -
                this->players[i]->getBounds().width / 2.f,
            this->players[i]->getPosition().y -
                this->players[i]->getBounds().height / 2.f -
                followPlayerTexts[i].getGlobalBounds().height -
                20.f);
        this->followPlayerTexts[i].setString("Player: " + std::to_string(i + 1) + "\n" +
                                             "HP: " + players[i]->getHpS());
    }
}

void Game::Update()
{
    // Update timer
    if (enemySpawnTimer < enemySpawnTimerMax)
        enemySpawnTimer++;

    // Enemy spawn
    if (enemySpawnTimer >= enemySpawnTimerMax)
    {
        enemys.push_back(new Enemy(
            &this->textures.at(ENEMY), this->window->getSize(),
            Vector2f(0.f, 0.f), Vector2f(-1.f, 0.f), Vector2f(0.5f, 0.5f),
            MOVE_LEFT, rand() % 3 + 1, 3, 1));
        enemySpawnTimer = 0;
    }

    for (auto &p : players)
    {
        // Player Update
        p->Update(this->window->getSize());
        if (p->getBullets().size() > 0)
        { // Bullet Update
            for (size_t i = 0; i < p->getBullets().size(); i++)
            {
                bool flag = true;
                p->getBullets()[i]->Update();

                // Bullet collision with window bounds
                if (p->getBullets()[i]->getPosition().x > this->window->getSize().x)
                {
                    delete p->getBullets()[i];
                    p->getBullets().erase(p->getBullets().begin() + i);
                    return;
                }

                // Bullet collision with enemy
                for (size_t j = 0; j < enemys.size() && flag; j++)
                {
                    if (p->getBullets()[i]->getBounds().intersects(enemys[j]->getBounds()))
                    {
                        enemys[j]->TakeDamage(1);
                        delete p->getBullets()[i];
                        p->getBullets().erase(p->getBullets().begin() + i);
                        flag = false;
                        if (enemys[j]->isDead())
                        {
                            delete enemys[j];
                            enemys.erase(enemys.begin() + j);
                            break;
                        }
                    }
                }
            }
        }
        // Player sideGunUp Bullet collision with enemy
        for (size_t j = 0; j < enemys.size(); j++)
        {
            for (size_t k = 0; k < p->getWeapons().size(); k++)
            {

                for (size_t l = 0; l < p->getWeapons()[k]->getBullets().size(); l++)
                {
                    if (p->getWeapons()[k]->getBullets()[l]->getBounds().intersects(enemys[j]->getBounds()))
                    {
                        enemys[j]->TakeDamage(1);
                        delete p->getWeapons()[k]->getBullets()[l];
                        p->getWeapons()[k]->getBullets().erase(p->getWeapons()[k]->getBullets().begin() + l);
                        if (enemys[j]->isDead())
                        {
                            delete enemys[j];
                            enemys.erase(enemys.begin() + j);
                            return;
                        }
                    }
                }
            }
        }
    }

    // UI Update
    this->UpdateUI();

    // Enemy Update
    for (size_t i = 0; i < enemys.size(); i++)
    {
        enemys[i]->Update();

        // Enemy collision with window bounds
        if (enemys[i]->getPosition().x <= 0 - enemys[i]->getBounds().width)
        {
            delete enemys[i];
            enemys.erase(enemys.begin() + i);
            return;
        }

        // Enemy collision with player
        for (size_t j = 0; j < players.size(); j++)
        {
            if (enemys[i]->getBounds().intersects(players[j]->getBounds()))
            {
                players[j]->TakeDamage(1);
                delete enemys[i];
                enemys.erase(enemys.begin() + i);

                if (players[j]->isDead())
                {
                    players.erase(players.begin() + j);
                    if (players.size() == 0)
                    {
                        std::cout << "Game Over" << std::endl;
                        this->window->close();
                    }
                    return;
                }

                break;
            }
        }
    }
}

void Game::RenderUI()
{
    for (size_t i = 0; i < players.size(); i++)
    {
        this->window->draw(this->followPlayerTexts[i]);
        this->window->draw(this->stationaryTexts[i]);
    }
}

void Game::Render()
{
    this->window->clear();

    // Render items
    for (auto &p : players)
    {
        p->Render(*this->window);
    }

    // Render enemys
    for (auto &e : enemys)
    {
        e->Render(*this->window);
    }

    // Render UI
    this->RenderUI();

    this->window->display();
}
