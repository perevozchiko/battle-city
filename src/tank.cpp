#include "include/tank.h"

Tank::Tank(sf::Texture& _texture, int _x, int _y, int _width, int _height) :
    texture {_texture}, position{_x, _y}, size{_width, _height}
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
    sprite.setOrigin(size.x/2, size.y/2);
    sprite.setPosition(position.x, position.y);
}

void Tank::update(const sf::Time& time)
{
    switch (dir)
    {
    case Direction::LEFT:
        position.x++;
        break;
    }
}
