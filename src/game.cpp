#include "game.h"

const Time TimePerFrame = sf::seconds(1.0f/60.f);

void Game::handleInput(Keyboard::Key key, bool isPressed)
{
    switch (key)
    {
    case Keyboard::Left:
        if (isPressed)
        {
            Direction::LEFT;
        }
    default:
        break;

    }
}

Game::Game() :
    window(sf::VideoMode(640, 480), "testSfml1"),
    gameTexture(),
    heroTank(gameTexture, 150, 150, 32, 32)
{    
    gameTexture.loadFromFile("sprite.bmp");
}

void Game::run()
{
    Clock clock;
    Time timeSinceLastUpdate = sf::Time::Zero;
    while (window.isOpen())
    {
        Time elapsedTime = clock.restart();
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

void Game::update(const Time &elapsedTime)
{

}

void Game::processEvents()
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (Event::key)
    }
}
void Game::render()
{
    window.clear();
    window.draw(heroTank.getSprite());
    window.display();
}
