#include "game.h"
#include <vector>
std::vector <Object> manysprite;
Game::Game() :
    window(sf::VideoMode(Conf::WindowWidth, Conf::WindowHeight), Conf::GameName),
    gameTexture(),
    player(gameTexture, Conf::WindowWidth/2, Conf::WindowHeight/2, Conf::SizeTexture, Conf::SizeTexture),
    enemy(gameTexture, Conf::WindowWidth/3, Conf::WindowHeight/3, Conf::SizeTexture, Conf::SizeTexture)
{
    gameTexture.loadFromFile("resources/images/sprite.bmp");

    for (int i = 0; i < 100; i++)
    {
        Object many(gameTexture, Conf::WindowWidth/5 + 2*i, Conf::WindowHeight/5+ 2*i, Conf::SizeTexture, Conf::SizeTexture);
        manysprite.push_back(many);
    }
    font.loadFromFile("resources/fonts/vapor_trails_remixed.otf");
    fpsInfo.text.setFont(font);
    fpsInfo.text.setPosition(5.0f, 5.0f);
    fpsInfo.text.setCharacterSize(12);

}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

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
        updateFPS(elapsedTime);
        render();
    }
}

void Game::adaptPlayerPosition()
{
    sf::Vector2f position = player.getPosition();

    position.x = std::max(position.x, static_cast<float>(player.getSize().x/2));
    position.x = std::min(position.x, static_cast<float>(Conf::WindowWidth - player.getSize().x/2));

    position.y = std::max(position.y, static_cast<float>(player.getSize().y/2));
    position.y = std::min(position.y, static_cast<float>(Conf::WindowHeight - player.getSize().y/2));

    player.setPosition(position);
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

    enemyMoving();

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

void Game::enemyMoving()
{

    int random = getRandomNumber(1,4);
    random = 1;
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

void Game::update(const sf::Time &elapsedTime)
{

    player.update(elapsedTime);

    enemy.update(elapsedTime);

    adaptPlayerPosition();
    for (int i = 0; i < manysprite.size(); i++)
    {
        manysprite[i].update(elapsedTime);
    }
}


void Game::render()
{
    window.clear();

    window.draw(player.getSprite());
    window.draw(enemy.getSprite());

    for (int i = 0; i < manysprite.size(); i++)
    {
        window.draw(manysprite[i].getSprite());
    }
    window.draw(fpsInfo.text);
    window.display();
}


int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // равномерно распределяем рандомное число в нашем диапазоне
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
