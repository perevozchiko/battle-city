#include "game.h"

const Time TimePerFrame = sf::seconds(1.0f/60.f);

Game::Game() :
    window(VideoMode(640, 480), "Battle City"),
    gameTexture(),
    heroTank(gameTexture, 320, 240, 32, 32)
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

void Game::processEvents()
{
    Event event;
    while (window.pollEvent(event))
    {
        switch(event.type)
        {
        case Event::Closed:
            window.close();
            break;

        case Event::KeyPressed:
            handleInput(event.key.code, true);
            break;

        case Event::KeyReleased:
            handleInput(event.key.code, false);
            break;

        default:
            break;
        }
    }
}

void Game::handleInput(Keyboard::Key key, bool isPressed)
{
    switch (key)
    {
    case Keyboard::Left:
        if (isPressed)
        {
            heroTank.setDir(Tank::Direction::LEFT);
        }
        else
        {
            heroTank.setDir(Tank::Direction::NO);
        }
        break;
    case Keyboard::Right:
        if (isPressed)
        {
            heroTank.setDir(Tank::Direction::RIGHT);
        }
        else
        {
            heroTank.setDir(Tank::Direction::NO);
        }
        break;
    case Keyboard::Up:
        if (isPressed)
        {
            heroTank.setDir(Tank::Direction::UP);
        }
        else
        {
            heroTank.setDir(Tank::Direction::NO);
        }
        break; case Keyboard::Down:
        if (isPressed)
        {
            heroTank.setDir(Tank::Direction::DOWN);
        }
        else
        {
            heroTank.setDir(Tank::Direction::NO);
        }
        break;
    default:
        break;
    }
}

void Game::update(const Time &elapsedTime)
{
    heroTank.update();
}

void Game::render()
{
    window.clear();
    window.draw(heroTank.getSprite());
    window.display();
}

