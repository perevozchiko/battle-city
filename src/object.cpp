#include "object.h"
#include <iostream>



Object::Object(Conf::Type _type, sf::Texture& _texture, int _x, int _y, sf::Vector2i _offset, int _size) :
    texture (_texture),
    position(_x, _y),
    size(_size),
    speed(0.f),
    dx(0),
    dy(0),
    offset(_offset),
    type(_type)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(offset.x, offset.y, size, size));
    sprite.setOrigin(size/2, size/2);
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
    if (type == Conf::Type::Player)
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

int Object::getSize() const
{
    return size;
}




