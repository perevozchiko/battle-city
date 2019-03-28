#include "player.h"
#include <iostream>
namespace BattleCity {

Player::Player(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2i position):
    Entity(position),
    size(SET::SIZE_TILE_TANK),
    direction(SET::Direction::UP)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(offset, size));
    sprite.setOrigin(size.x/2, size.y/2);
}

void Player::setDirection(const SET::Direction &_direction)
{
    setSpeed(SET::PLAYER_SPEED);

    direction = _direction;
    switch (direction)
    {
    case SET::Direction::LEFT:
        setRotation(-90.0f);
        break;
    case SET::Direction::RIGHT:
        setRotation(90.0f);
        break;
    case SET::Direction::UP:
        setRotation(0.0f);
        break;
    case SET::Direction::DOWN:
        setRotation(180.0f);
        break;
    }
}

sf::Vector2i Player::getSize() const
{
    return size;
}

SET::Direction Player::getDirection() const
{
    return direction;
}

void Player::update(const sf::Time &elapsedTime)
{
    int dx = 0;
    int dy = 0;
    switch (direction)
    {
    case SET::Direction::LEFT:
        dx = -getSpeed();
        dy = 0;
        break;
    case SET::Direction::RIGHT:
        dx = getSpeed();
        dy = 0;
        break;
    case SET::Direction::UP:
        dx = 0;
        dy = -getSpeed();
        break;
    case SET::Direction::DOWN:
        dx = 0;
        dy = getSpeed();
        break;
    }
    setSpeed(0);

    if(getCollisionDetected() == false)
    {
        move(dx * elapsedTime.asSeconds(), dy * elapsedTime.asSeconds());
    }
    else
    {
        move(0,0);
        setCollisionDetected(false);
    }
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}


void Player::handleRealTimeInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        setDirection(SET::Direction::LEFT);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        setDirection(SET::Direction::RIGHT);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        setDirection(SET::Direction::UP);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        setDirection(SET::Direction::DOWN);
    }
}

sf::IntRect Player::getGlobalRect() const
{
    sf::Vector2i pos = getPosition();
    sf::IntRect r =
    {
        int(std::round(sprite.getGlobalBounds().left)),
        int(std::round(sprite.getGlobalBounds().top)),
        int(std::round(sprite.getGlobalBounds().width)),
        int(std::round(sprite.getGlobalBounds().height))
    };
    r.left = pos.x - r.width/2;
    r.top = pos.y - r.height/2;
    return r;
}

void Player::adaptPlayerPosition()
{
    setPosition(adaptPosition());
}
} //namespace BattleCity
