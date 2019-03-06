#include "tank.h"
#include <iostream>

Tank::Tank(Texture& _texture, int _x, int _y, int _width, int _height) :
    texture {_texture},
    position{_x, _y},
    size{_width, _height},
    speed{0.0f},
    dx{0},
    dy{0}
{
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, size.x, size.y));
    sprite.setOrigin(size.x/2, size.y/2);
    sprite.setPosition(position.x, position.y);
}

void Tank::update(Time timeMove)
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
    sprite.move(dx * timeMove.asSeconds(), dy * timeMove.asSeconds());

}

void Tank::setDir(Direction dir)
{
    speed = 40.0f;
    this->dir = dir;
    switch (dir)
    {
    case Tank::Direction::LEFT:
        sprite.setRotation(-90.0f);
        break;
    case Tank::Direction::RIGHT:
        sprite.setRotation(90.0f);
        break;
    case Tank::Direction::UP:
        sprite.setRotation(0.0f);
        break;
    case Tank::Direction::DOWN:
        sprite.setRotation(180.0f);
        break;
    default:
        break;
    }
}

void Tank::setSpeed(float speed)
{
    this->speed = speed;
}



