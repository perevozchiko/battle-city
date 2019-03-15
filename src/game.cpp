#include "game.h"
#include <vector>


Game::Game() :
    window(sf::VideoMode(Conf::WindowWidth, Conf::WindowHeight), Conf::GameName, sf::Style::Default , sf::ContextSettings(24,8,2)),
    player()
{
        font.loadFromFile("resources/fonts/vapor_trails_remixed.otf");
        fpsInfo.text.setFont(font);
        fpsInfo.text.setPosition(5.0f, 5.0f);
        fpsInfo.text.setCharacterSize(12);

        for (int i = 0; i < 60; i++)
        {
            Enemy _enemy;
            enemies.push_back(_enemy);
        }
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
                enemyTime -= Conf::TimePerFrame;
                enemy.changeDirectionMoving();
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
for (Enemy _enemy : enemies)
{
   _enemy.update(elapsedTime);
   _enemy.adaptEnemyPosition();
}
}

void Game::render()
{
    window.clear();

    window.draw(player.getSprite());
    window.draw(enemy.getSprite());


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

