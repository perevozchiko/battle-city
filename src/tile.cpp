#include "include/tile.h"

namespace BattleCity {

Tile::Tile(const sf::Texture &texture, sf::Vector2i _offset) :
    Entity ({0,0}),
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

sf::FloatRect Tile::getGlobalRect() const
{
    auto pos = getPosition();
    auto r = sprite.getGlobalBounds();
    r.left = pos.x;
    r.top = pos.y;
    return r;
}


void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}
} //namespace BattleCity
