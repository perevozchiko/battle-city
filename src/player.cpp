#include "player.h"
#include <iostream>



Player::Player(Texture& _texture, int _x, int _y, int _width, int _height) :
    texture (_texture),
    position(_x, _y),
    size(_width, _height),
    speed(0),
    dx(0),
    dy(0)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, size.x, size.y));
    sprite.setOrigin(size.x/2, size.y/2);
    sprite.setPosition(position.x, position.y);
}

void Player::update(Time timeMove)
{
    switch (dir)
    {
    case Direction::LEFT:
        dx = -speed;
        dy = 0;
        break;
    case Direction::RIGHT:
        dx = speed;
        dy = 0;
        break;
    case Direction::UP:
        dx = 0;
        dy = -speed;
        break;
    case Direction::DOWN:
        dx = 0;
        dy = speed;
        break;
    default:
        break;
    }
    speed = 0;
    sprite.move(dx, dy);
}

void Player::setDir(Direction _dir)
{
    speed = Conf::SPEED;
    dir = _dir;
    switch (dir)
    {
    case Player::Direction::LEFT:
        sprite.setRotation(-90.0f);
        break;
    case Player::Direction::RIGHT:
        sprite.setRotation(90.0f);
        break;
    case Player::Direction::UP:
        sprite.setRotation(0.0f);
        break;
    case Player::Direction::DOWN:
        sprite.setRotation(180.0f);
        break;
    default:
        break;
    }
}

void Player::setSpeed(float _speed)
{
    speed = _speed;
}

Vector2f Player::getPosition() const
{
    return position;
}

void Player::setPosition(const Vector2f &value)
{
    position = value;
}



