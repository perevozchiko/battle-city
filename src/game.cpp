#include "game.h"
#include <vector>
#include <iostream>

Game::Game() :
    window(sf::VideoMode(Conf::WindowWidth, Conf::WindowHeight), Conf::GameName, sf::Style::Default , sf::ContextSettings(24,8,2)),
    tile(),
    player(),
    enemy()
{
    for (int i = 0; i < 3; i++)
    {
        sf::Vector2f pos = {Conf::WindowWidth * i/2 + (i%2) * 16.f, 16.f};
        enemy.setPosition(pos);
        enemy.setTextureRectange(sf::IntRect(224, 809, 32, 32));
        enemies.push_back(enemy);
    }

    // Настройка отображения FPS в углу
    font.loadFromFile(Conf::PathFonts);
    fpsInfo.text.setFont(font);
    fpsInfo.text.setPosition(5.f, 5.f);
    fpsInfo.text.setCharacterSize(12);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time enemyTime = sf::Time::Zero;
    while (window.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > Conf::TimePerFrame)
        {
            timeSinceLastUpdate -= Conf::TimePerFrame;

            processEvents();
            update(Conf::TimePerFrame);
        }

        enemyTime += elapsedTime;


        if (enemyTime.asSeconds() > 1)
        {
            while (enemyTime > Conf::TimePerFrame)
            {

                enemyTime -= Conf::TimePerFrame;
            }
            RandomGen gen;
            int i = gen(0, enemies.size());

            enemies[i].changeDirectionMoving();
        }

        updateFPS(elapsedTime);
        render();
    }

}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        default:
            break;
        }
    }
    player.handleRealTimeInput();

}

void Game::update(const sf::Time &elapsedTime)
{

    player.update(elapsedTime);
    player.adaptPlayerPosition();
    for (auto& enemy : enemies)
    {
        enemy.update(elapsedTime);
        enemy.adaptEnemyPosition();
    }

}

void Game::render()
{
    window.clear();



    window.draw(player.getSprite());


    for (auto& enemy : enemies)
    {
        window.draw(enemy.getSprite());
    }

    for (std::size_t rows = 0; rows < HEIGHTMAP; rows++)
    {
        for (std::size_t cols = 0; cols < WIDTHMAP; cols++)
        {
            if (testMap[rows][cols] == '*')
            {
                tile.setTextureRectange(sf::IntRect(0, 272, 16, 16));
            }
            if (testMap[rows][cols] == ' ')
            {
                tile.setTextureRectange(sf::IntRect(308, 147, 16, 16));
            }
            tile.getSprite().setOrigin(0, 0);
            tile.getSprite().setPosition(cols * 16.f, rows * 16.f);
            window.draw(tile.getSprite());
        }
    }
    window.draw(fpsInfo.text);
    window.display();
}



void Game::updateFPS(const sf::Time &elapsedTime)
{
    fpsInfo.updateTime += elapsedTime;
    ++fpsInfo.frame;

    if (fpsInfo.updateTime >= sf::seconds(1.f))
    {
        fpsInfo.text.setString("FPS = " + std::to_string(fpsInfo.frame) + "\n");
        fpsInfo.updateTime -= sf::seconds(1.f);
        fpsInfo.frame = 0;
    }
}

