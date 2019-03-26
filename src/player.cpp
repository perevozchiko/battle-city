#include "player.h"
#include <iostream>
namespace BattleCity {

Player::Player(sf::Vector2i _offset, const sf::Texture &texture):
    offset(_offset),
    size(SET::SIZE_TILE_TANK),
    position({280,620}),
    speed(0),
    direction(SET::Direction::UP)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(offset, size));
    sprite.setOrigin(size.x/2, size.y/2);
    sprite.setPosition(position);
}

void Player::setDirection(const SET::Direction &_direction)
{
    speed = SET::TANK_SPEED;
    direction = _direction;
    switch (direction)
    {
    case SET::Direction::LEFT:
        sprite.setRotation(-90.0f);
        break;
    case SET::Direction::RIGHT:
        sprite.setRotation(90.0f);
        break;
    case SET::Direction::UP:
        sprite.setRotation(0.0f);
        break;
    case SET::Direction::DOWN:
        sprite.setRotation(180.0f);
        break;
    }
}

void Player::update(const sf::Time &elapsedTime)
{
    float dx = 0;
    float dy = 0;
    switch (getDirection())
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

    sprite.move(dx * elapsedTime.asSeconds(), dy * elapsedTime.asSeconds());
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

void Player::adaptPosition()
{
    sf::Vector2f position = sprite.getPosition();

    position.x = std::max(position.x, static_cast<float>(getSize().x/2));
    position.x = std::min(position.x, static_cast<float>(SET::WINDOW_WIDTH - getSize().x/2));

    position.y = std::max(position.y, static_cast<float>(getSize().y/2));
    position.y = std::min(position.y, static_cast<float>(SET::WINDOW_HEIGHT - getSize().y/2));

    sprite.setPosition(position);
}

float Player::getSpeed() const
{
    return speed;
}

void Player::setSpeed(float value)
{
    speed = value;
}

sf::Vector2f Player::getPosition() const
{
    return sprite.getPosition();
}

void Player::setPosition(const sf::Vector2f &value)
{
    sprite.setPosition(value);
}

SET::Direction Player::getDirection() const
{
    return direction;
}

sf::Vector2i Player::getOffset() const
{
    return offset;
}

void Player::setOffset(const sf::Vector2i &value)
{
    offset = value;
}

sf::Sprite& Player::getSprite()
{
    return sprite;
}

void Player::setSprite(const sf::Sprite &value)
{
    sprite = value;
}

sf::Vector2i Player::getSize() const
{
    return size;
}

void Player::setSize(const sf::Vector2i &value)
{
    size = value;
}

} //namespace BattleCity
