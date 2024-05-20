// Game.cpp

#include "../include/Game.hpp"
#include "../include/Weapons/PeaShooter.hpp"
#include <iostream>

Game::Game(RenderWindow *window) : window(window)
{
    // Window
    // this->window->setFramerateLimit(60);
    this->dtMultiplier = 60.f;

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

void Game::createPlayers()
{
    this->players.push_back(createPlayer(this->textures, this->window->getSize(), Keyboard::W, Keyboard::S, Keyboard::A, Keyboard::D, Keyboard::Space));
    this->players.push_back(createPlayer(this->textures, this->window->getSize(), Keyboard::Up, Keyboard::Down, Keyboard::Left, Keyboard::Right, Keyboard::RShift));
}

Player *Game::createPlayer(std::vector<Texture> &textures, Vector2u windowBounds,
                           int upKey, int downKey, int leftKey, int rightKey, int fireKey)
{
    return new Player(textures, windowBounds, upKey, downKey, leftKey, rightKey, fireKey);
}

void Game::InItUi()
{
    if (!this->font.loadFromFile(resourcePathsFonts.at(DOSIS_LIGHT)))
    {
        std::cerr << "Failed to load font: " << resourcePathsFonts.at(DOSIS_LIGHT) << std::endl;
    }
    this->followPlayerText.setFont(font);
    this->stationaryText.setFont(font);

    // Follow Player Text
    this->followPlayerText.setCharacterSize(24);
    this->followPlayerText.setFillColor(Color::White);

    // Stationary Text
    this->stationaryText.setCharacterSize(12);
    this->stationaryText.setFillColor(Color::White);

    // Player Exp Bar
    this->playerExpBar.setSize(Vector2f(110.f, 10.f));
    this->playerExpBar.setFillColor(Color(0.f, 100.f, 200.f, 200.f));


    // Game Over Text
    if (!this->gameOverFont.loadFromFile(resourcePathsFonts.at(GAME_OVER)))
    {
        std::cerr << "Failed to load font: " << resourcePathsFonts.at(GAME_OVER) << std::endl;
    }
    this->gameOverText.setFont(gameOverFont);
    this->gameOverText.setCharacterSize(60);
    this->gameOverText.setFillColor(Color::White);
    this->gameOverText.setString("Game Over");
    this->gameOverText.setPosition(
        0.f - this->gameOverText.getGlobalBounds().width,
        this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);
}

void Game::UpdateUI(int index)
{
    if (index >= players.size())
    {
        std::cerr << "Player index out of bounds" << std::endl;
    }
    else
    {
        this->followPlayerText.setPosition(
            this->players[index]->getPosition().x -
                this->players[index]->getBounds().width / 2.f,

            this->players[index]->getPosition().y -
                this->players[index]->getBounds().height / 2.f -
                this->followPlayerText.getGlobalBounds().height -
                20.f);

        this->followPlayerText.setString(
            "Player: " + std::to_string(players[index]->getPlayerNumber()) + "\n" +
            "HP: " + players[index]->getHpS());
    }
    // Exp Bar
    this->playerExpBar.setPosition(
        this->players[index]->getPosition().x - this->players[index]->getBounds().width / 2.f + 10.f,
        this->players[index]->getPosition().y + this->players[index]->getBounds().height / 2.f + 10.f);

    this->playerExpBar.setScale(
        static_cast<float>(this->players[index]->getExp()) / static_cast<float>(this->players[index]->getExpNext()), 1.f);

}

void Game::Update(const float &dt)
{
    if (!gameOver)
    {
        // Update timer
        if (enemySpawnTimer < enemySpawnTimerMax)
            enemySpawnTimer += 1.f * dt * this->dtMultiplier;

        // Enemy spawn
        if (enemySpawnTimer >= enemySpawnTimerMax)
        {
            enemys.push_back(new Enemy(
                &this->textures.at(ENEMY), this->window->getSize(),
                Vector2f(0.f, 0.f), Vector2f(-1.f, 0.f), Vector2f(0.5f, 0.5f),
                MOVE_LEFT, 2.f, rand() % 3 + 1, 3, 1));
            enemySpawnTimer = 0;
        }

        for (auto &p : players)
        {
            // Player Update
            p->Update(this->window->getSize(), dt);
            if (p->getBullets().size() > 0)
            { // Bullet Update
                for (size_t i = 0; i < p->getBullets().size(); i++)
                {
                    bool flag = true;
                    p->getBullets()[i]->Update(dt);

                    // Bullet collision with window bounds
                    if (p->getBullets()[i]->getPosition().x > this->window->getSize().x)
                    {
                        delete p->getBullets()[i];
                        p->getBullets().erase(p->getBullets().begin() + i);
                        continue;
                    }

                    // Bullet collision with enemy
                    for (size_t j = 0; j < enemys.size() && flag; j++)
                    {
                        if (p->getBullets()[i]->getBounds().intersects(enemys[j]->getBounds()))
                        {
                            enemys[j]->TakeDamage(p->getBullets()[i]->getDamage());
                            delete p->getBullets()[i];
                            p->getBullets().erase(p->getBullets().begin() + i);
                            flag = false;
                            if (enemys[j]->isDead())
                            {
                                p->gainExp(enemys[j]->getExp());
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
                            enemys[j]->TakeDamage(p->getWeapons()[k]->getBullets()[l]->getDamage());
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

        // Enemy Update
        for (size_t i = 0; i < enemys.size(); i++)
        {
            enemys[i]->Update(dt);

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
                            this->gameOver = true;
                            return;
                        }
                        return;
                    }

                    break;
                }
            }
        }
    }
    else
    {
        this->gameOverText.move(10.f * dt * dtMultiplier, 0.f);
        if (this->gameOverText.getPosition().x > this->window->getSize().x)
        {
            this->gameOverText.setPosition(
                0.f - this->gameOverText.getGlobalBounds().width,
                this->gameOverText.getPosition().y);
        }
    }
}

void Game::RenderUI()
{
    if (!gameOver)
    {

        for (size_t i = 0; i < players.size(); i++)
        {
            this->UpdateUI(i);
            this->window->draw(this->followPlayerText);
            // this->window->draw(this->stationaryText);
            this->window->draw(this->playerExpBar);
        }
    }
    else
    {
        this->window->draw(this->gameOverText);
    }
}

void Game::Render()
{
    this->window->clear();
    if (!gameOver)
    { // Render items
        for (auto &p : players)
        {
            p->Render(*this->window);
        }

        // Render enemys
        for (auto &e : enemys)
        {
            e->Render(*this->window);
        }
    }
    // Render UI
    this->RenderUI();

    this->window->display();
}
