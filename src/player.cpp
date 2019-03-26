#include "player.h"
#include <iostream>
namespace BattleCity {

Player::Player(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2f position):
    Entity(position),
    size(SET::SIZE_TILE_TANK),
    direction(SET::Direction::UP)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(offset, size));
    sprite.setOrigin(size.x/2, size.y/2);
    sprite.setPosition(position);
}

void Player::setDirection(const SET::Direction &_direction)
{
    setSpeed(SET::TANK_SPEED);
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

    move(dx * elapsedTime.asSeconds(), dy * elapsedTime.asSeconds());
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

sf::FloatRect Player::getGlobalRect() const
{
    auto pos = getPosition();
    auto r = sprite.getGlobalBounds();
    r.left = pos.x - r.width/2;
    r.top = pos.y - r.height/2;
    return r;
}

void Player::adaptPosition()
{
    sf::Vector2f position = getPosition();

    position.x = std::max(position.x, static_cast<float>(getSize().x/2));
    position.x = std::min(position.x, static_cast<float>(SET::WINDOW_WIDTH - getSize().x/2));

    position.y = std::max(position.y, static_cast<float>(getSize().y/2));
    position.y = std::min(position.y, static_cast<float>(SET::WINDOW_HEIGHT - getSize().y/2));

    setPosition(position);
}
} //namespace BattleCity
