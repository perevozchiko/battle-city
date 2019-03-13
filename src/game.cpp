#include "game.h"

Game::Game() :
    window(sf::VideoMode(Conf::WindowWidth, Conf::WindowHeight), Conf::GameName),
    gameTexture(),
    heroTank(gameTexture, Conf::WindowWidth/2, Conf::WindowHeight/2, Conf::SizeTexture, Conf::SizeTexture)
{
    gameTexture.loadFromFile("sprite.bmp");
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

        render();
    }
}

void Game::adaptPlayerPosition()
{
    sf::Vector2f position = heroTank.getPosition();

    position.x = std::max(position.x, heroTank.getHalfSize().x);
    position.x = std::min(position.x, Conf::WindowWidth - heroTank.getHalfSize().x);

    position.y = std::max(position.y, heroTank.getHalfSize().y);
    position.y = std::min(position.y, Conf::WindowHeight - heroTank.getHalfSize().y);

    heroTank.setPosition(position);

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
        heroTank.setDir(Player::Direction::LEFT);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        heroTank.setDir(Player::Direction::RIGHT);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        heroTank.setDir(Player::Direction::UP);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        heroTank.setDir(Player::Direction::DOWN);
    }
}

void Game::update(const sf::Time &elapsedTime)
{

    heroTank.update();
    adaptPlayerPosition();
}


void Game::render()
{
    window.clear();

    window.draw(heroTank.getSprite());

    window.display();
}
