#include "game.h"

const sf::Time TimePerFrame = sf::seconds(1.0f/60.f);

void Game::handleInput(sf::Keyboard::Key key, bool isPressed)
{
    switch (key)
    {
    case sf::Keyboard::Left:
        if (isPressed)
        {
            Direction::LEFT;
        }
    default:
        break;

    }
}

Game::Game() :
    window(sf::VideoMode(640, 480), "Battle City"),
    gameTexture(),
    heroTank(gameTexture, 150, 150, 32, 32)
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

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processEvents();
            update(TimePerFrame);
        }

        render();
    }
}

void Game::update(const sf::Time &elapsedTime)
{
    switch()

}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::render()
{
    window.clear();
    window.draw(heroTank.getSprite());
    window.display();
}
