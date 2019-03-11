#include "game.h"

Game::Game() :
    window(VideoMode(Conf::WINDOW_WIDTH, Conf::WINDOW_HEIGHT), Conf::GAME_NAME),
    gameTexture(),
    heroTank(gameTexture, Conf::WINDOW_WIDTH/2, Conf::WINDOW_HEIGHT/2, Conf::SIZE_TEXTURE, Conf::SIZE_TEXTURE)
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
        while (timeSinceLastUpdate > Conf::TIME_PER_FRAME)
        {
            timeSinceLastUpdate -= Conf::TIME_PER_FRAME;
            processEvents();
            update(Conf::TIME_PER_FRAME);
        }

        render();
    }
}

void Game::adaptPlayerPosition()
{
    Vector2f position = heroTank.getPosition();
    float halfSizeX = heroTank.getSize().x / 2.0f;
    float halfSizeY = heroTank.getSize().y / 2.0f;

    position.x = std::max(position.x, halfSizeX);
    position.x = std::min(position.x, Conf::WINDOW_WIDTH - halfSizeX);

    position.y = std::max(position.y, halfSizeY);
    position.y = std::min(position.y, Conf::WINDOW_HEIGHT - halfSizeY);

    Vector2f pos (2.0f, 5.0f);
    heroTank.setPosition(pos);

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


    adaptPlayerPosition();
    heroTank.update(elapsedTime);


}


void Game::render()
{
    window.clear();

    window.draw(heroTank.getSprite());

    window.display();
}



//void World::adaptPlayerPosition()
//{
//  // Keep player's position inside the screen bounds, at least borderDistance units from the border
//  sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
//  const float borderDistance = 40.f;

//  sf::Vector2f position = mPlayerAircraft->getPosition();
//  position.x = std::max(position.x, viewBounds.left + borderDistance);
//  position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
//  position.y = std::max(position.y, viewBounds.top + borderDistance);
//  position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
//  mPlayerAircraft->setPosition(position);
//}
