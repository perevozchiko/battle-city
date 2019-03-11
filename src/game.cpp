#include "game.h"


const Time TimePerFrame = sf::seconds(1.0f/30.f);
const int WidthResolution = 640;
const int HeightResolution = 480;

Game::Game() :
    window(VideoMode(WidthResolution, HeightResolution), "Battle City"),
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

        default:
            break;
        }
    }
    handleRealTimeInput();
}

void Game::handleRealTimeInput()
{
    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        heroTank.setDir(Player::Direction::LEFT);
    }

    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        heroTank.setDir(Player::Direction::RIGHT);
    }

    if (Keyboard::isKeyPressed(Keyboard::Up))
    {
        heroTank.setDir(Player::Direction::UP);
    }

    if (Keyboard::isKeyPressed(Keyboard::Down))
    {
        heroTank.setDir(Player::Direction::DOWN);
    }
}

void Game::update(const Time &elapsedTime)
{
    if (heroTank.getSprite().getPosition().x - heroTank.getSize().x/2 < 0)
    {
        heroTank.collisionDetect = true;
    }

    heroTank.update(elapsedTime);
}


void Game::render()
{
    window.clear();

    window.draw(heroTank.getSprite());

    window.display();
}

