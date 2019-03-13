#include "object.h"
#include <iostream>



Object::Object(sf::Texture& _texture, int _x, int _y, int _width, int _height) :
    texture (_texture),
    position(_x, _y),
    size(_width, _height),
    speed(0.f),
    dx(0),
    dy(0)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
    sprite.setOrigin(size.x/2, size.y/2);
    sprite.setPosition(position.x, position.y);

}

void Object::update(const sf::Time elapsedTime)
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
    }
    speed = 0;
    sprite.move(dx * elapsedTime.asSeconds(), dy * elapsedTime.asSeconds());
}

void Object::setDir(Direction _dir)
{
    speed = Conf::TankSpeed;
    dir = _dir;
    switch (dir)
    {
    case Object::Direction::LEFT:
        sprite.setRotation(-90.0f);
        break;
    case Object::Direction::RIGHT:
        sprite.setRotation(90.0f);
        break;
    case Object::Direction::UP:
        sprite.setRotation(0.0f);
        break;
    case Object::Direction::DOWN:
        sprite.setRotation(180.0f);
        break;
    }
}

Object::Direction Object::getDir() const
{
    return dir;
}

void Object::setSpeed(float _speed)
{
    speed = _speed;
}

sf::Vector2f Object::getPosition() const
{
    return sprite.getPosition();
}

void Object::setPosition(const sf::Vector2f &value)
{
    sprite.setPosition(value);
}


sf::Sprite Object::getSprite() const
{
    return sprite;
}

sf::Vector2i Object::getSize() const
{
    return size;
}




