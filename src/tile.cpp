#include "include/tile.h"

namespace BattleCity {

Tile::Tile(sf::Vector2i _offset, const sf::Texture &texture) :
    offset(_offset),
    size(SET::SIZE_TILE_MAP),
    type(SET::Tile::Empty)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(offset, size));
}

void Tile::update(const sf::Time &elapsedTime)
{

}

sf::Vector2f Tile::getPosition() const
{
    return sprite.getPosition();
}

void Tile::setPosition(const sf::Vector2f &value)
{
    sprite.setPosition(value);
}

sf::Sprite Tile::getSprite() const
{
    return sprite;
}

void Tile::setSprite(const sf::Sprite &value)
{
    sprite = value;
}

SET::Tile Tile::getType() const
{
    return type;
}

void Tile::setType(const int &value)
{
    switch (value)
    {
    case 0:
        type = SET::Tile::Empty;
        break;

    case 1:
        type = SET::Tile::Brick;
        break;

    case 2:
        type = SET::Tile::Concrete;
        break;

    case 3:
        type = SET::Tile::Shrub;
        break;

    case 4:
        type = SET::Tile::Ice;
        break;

    case 5:
        type = SET::Tile::Water;
        break;
    }
}

} //namespace BattleCity
