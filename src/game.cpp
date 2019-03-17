#include "game.h"
#include <vector>
#include <iostream>

Game::Game() :
    window(sf::VideoMode(Conf::WindowWidth, Conf::WindowHeight), Conf::GameName, sf::Style::Default , sf::ContextSettings(24,8,2)),
    player()
{
    for (int i = 0; i < 3; i++)
    {
        Enemy enemy;
        sf::Vector2f pos = {Conf::WindowWidth * i/2 + (i%2) * 16.f, 16.f};
        enemy.setPosition(pos);
        enemies.push_back(enemy);
    }



    // Настройка отображения FPS в углу
    font.loadFromFile("resources/fonts/vapor_trails_remixed.otf");
    fpsInfo.text.setFont(font);
    fpsInfo.text.setPosition(5.0f, 5.0f);
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


        if (enemyTime.asSeconds() > 3)
        {
            while (enemyTime > Conf::TimePerFrame)
            {
                for (auto& enemy : enemies)
                {
                    enemy.changeDirectionMoving();
                }
                enemyTime -= Conf::TimePerFrame;
            }

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


    window.draw(fpsInfo.text);
    window.display();
}



void Game::updateFPS(const sf::Time &elapsedTime)
{
    fpsInfo.updateTime += elapsedTime;
    ++fpsInfo.frame;

    if (fpsInfo.updateTime >= sf::seconds(1.0f))
    {
        fpsInfo.text.setString("FPS = " + std::to_string(fpsInfo.frame) + "\n");
        fpsInfo.updateTime -= sf::seconds(1.0f);
        fpsInfo.frame = 0;
    }
}

