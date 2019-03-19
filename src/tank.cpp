#include "include/tank.h"

Tank::Tank() :
Entity ({0, 0}, Conf::SizeTileTank, {Conf::WindowWidth/2, static_cast<float> (Conf::WindowHeight - Conf::SizeTileTank.y/2)})
{

}

Tank::Tank(sf::Vector2i _offset, sf::Vector2i _size, sf::Vector2f _position) :
Entity (_offset, _size, _position)
{

}

void Tank::setDir(Conf::Direction _dir)
{
    speed = Conf::TankSpeed;
    dir = _dir;
    switch (dir)
    {
    case Conf::Direction::LEFT:
        getSprite().setRotation(-90.0f);
        break;
    case Conf::Direction::RIGHT:
        getSprite().setRotation(90.0f);
        break;
    case Conf::Direction::UP:
        getSprite().setRotation(0.0f);
        break;
    case Conf::Direction::DOWN:
        getSprite().setRotation(180.0f);
        break;
    }
}

Conf::Direction Tank::getDir() const
{
    return dir;
}

void Tank::setSpeed(float _speed)
{
    speed = _speed;
}

float Tank::getSpeed() const
{
    return speed;
}

float Tank::getDx() const
{
    return dx;
}

void Tank::setDx(float value)
{
    dx = value;
}

float Tank::getDy() const
{
    return dy;
}

void Tank::setDy(float value)
{
    dy = value;
}

sf::Vector2f Tank::adaptPosition()
{
    sf::Vector2f position = getPosition();

    position.x = std::max(position.x, static_cast<float>(getSize().x/2));
    position.x = std::min(position.x, static_cast<float>(Conf::WindowWidth - getSize().x/2));

    position.y = std::max(position.y, static_cast<float>(getSize().y/2));
    position.y = std::min(position.y, static_cast<float>(Conf::WindowHeight - getSize().y/2));

    return position;
}

