#include "game.h"
#include <vector>


Game::Game() :
    window(sf::VideoMode(Conf::WindowWidth, Conf::WindowHeight), Conf::GameName, sf::Style::Default , sf::ContextSettings(24,8,2)),
    gameTexture(),
    player(Conf::Type::Player, gameTexture, Conf::WindowWidth/2, Conf::WindowHeight/2, {0,0}, Conf::SizeTexture)
{
    for (int i = 0; i < 60; i++)
    {
        auto posx = getRandomNumber(Conf::SizeTexture, Conf::WindowWidth - Conf::SizeTexture);
        auto posy = getRandomNumber(Conf::SizeTexture, Conf::WindowHeight - Conf::SizeTexture);
        Object enemy(Conf::Type::Enemy, gameTexture, posx, posy, {192, 808}, Conf::SizeTexture);
        enemies.push_back(enemy);
    }
    gameTexture.loadFromFile("resources/images/sprite.bmp");
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
                enemyTime -= Conf::TimePerFrame;
                enemyDirectionMoving();
            }

        }

        updateFPS(elapsedTime);
        render();
    }

}

void Game::adaptPlayerPosition()
{
    adaptPosition(player);
}

void Game::adaptPosition(Object &obj)
{
    sf::Vector2f position = obj.getPosition();

    position.x = std::max(position.x, static_cast<float>(obj.getSize()/2));
    position.x = std::min(position.x, static_cast<float>(Conf::WindowWidth - obj.getSize()/2));

    position.y = std::max(position.y, static_cast<float>(obj.getSize()/2));
    position.y = std::min(position.y, static_cast<float>(Conf::WindowHeight - obj.getSize()/2));

    obj.setPosition(position);
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
    handleRealTimeInput();

}

void Game::handleRealTimeInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player.setDir(Object::Direction::LEFT);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player.setDir(Object::Direction::RIGHT);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        player.setDir(Object::Direction::UP);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        player.setDir(Object::Direction::DOWN);
    }
}

void Game::enemyDirectionMoving()
{
    for (auto& enemy : enemies)
    {
        int random = getRandomNumber(1,4);
        switch(random)
        {
        case 1:
            enemy.setDir(Object::Direction::LEFT);
            break;
        case 2:
            enemy.setDir(Object::Direction::RIGHT);
            break;
        case 3:
            enemy.setDir(Object::Direction::UP);
            break;
        case 4:
            enemy.setDir(Object::Direction::DOWN);
            break;
        }
    }
}



void Game::update(const sf::Time &elapsedTime)
{

    player.update(elapsedTime);

    adaptPlayerPosition();
    for (auto& enemy : enemies)
    {
        enemy.update(elapsedTime);
        adaptPosition(enemy);
    }
}


void Game::render()
{
    window.clear();

    window.draw(player.getSprite());

    for (const auto& enemy : enemies)
    {
        window.draw(enemy.getSprite());
    }

    window.draw(fpsInfo.text);
    window.display();
}


int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
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

