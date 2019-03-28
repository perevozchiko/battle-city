#include "bullet.h"
namespace BattleCity {



Bullet::Bullet()
{

}

Bullet::Bullet(sf::Vector2i _position, SET::Direction _direction) :
    direction(_direction),
    visible(true)
{
//    switch (direction)
//    {
//        case SET::Direction::LEFT:
//        break;
//    }
}


SET::Direction Bullet::getDirection() const
{
    return direction;
}

void Bullet::setDirection(const SET::Direction &value)
{
    direction = value;
}

void Bullet::update(const sf::Time &elapsedTime)
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
    move(dx * elapsedTime.asSeconds(), dy * elapsedTime.asSeconds());
}

bool Bullet::getVisible() const
{
    return visible;
}

void Bullet::setVisible(bool value)
{
    visible = value;
}

int Bullet::getSpeed() const
{
    return speed;
}

void Bullet::setSpeed(int value)
{
    speed = value;
}

sf::Vector2i Bullet::getPosition() const
{
    return position;
}

void Bullet::setPosition(const sf::Vector2i &value)
{
    position = value;
}

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //    states.transform *= getTransform();
    //    target.draw(sprite, states);
}

} //namespace BattleCity
