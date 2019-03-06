#include "include/tank.h"

Tank::Tank(Texture& _texture, int _x, int _y, int _width, int _height) :
    texture {_texture},
    position{_x, _y},
    size{_width, _height},
    dir{Direction::NO},
    speed{0.0f}
{
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, size.x, size.y));
    sprite.setOrigin(size.x/2, size.y/2);
    sprite.setPosition(position.x, position.y);
}

void Tank::update()
{
    switch (dir)
    {
    case Direction::LEFT:
        sprite.move(-0.1f,0.0f);
        break;
    case Direction::RIGHT:
        sprite.move(0.1f,0.0f);
        break;
    case Direction::UP:
        sprite.move(0.0f,-0.1f);
        break;
    case Direction::DOWN:
        sprite.move(0.0f,0.1f);
        break;
    default:
        break;
    }
}

void Tank::setDir(Direction dir)
{
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



