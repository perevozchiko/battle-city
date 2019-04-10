#include "tile.h"

namespace BattleCity {

Tile::Tile(const sf::Texture &texture, sf::Vector2i _offset) :
    Entity ({0,0}),
    offset(_offset),
    size(SETTINGS::SIZE_TILE_MAP, SETTINGS::SIZE_TILE_MAP),
    type(SETTINGS::Tile::Empty)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(offset, size));
    setObjectType(SETTINGS::ObjectType::Tile);
}

Tile::~Tile()
{

}

void Tile::update(const sf::Time &elapsedTime)
{

}


SETTINGS::Tile Tile::getType() const
{
    return type;
}

void Tile::setType(const int &value)
{
    switch (value)
    {
    case 0:
        type = SETTINGS::Tile::Empty;
        break;

    case 1:
        type = SETTINGS::Tile::Brick;
        break;

    case 2:
        type = SETTINGS::Tile::Concrete;
        break;

    case 3:
        type = SETTINGS::Tile::Shrub;
        break;

    case 4:
        type = SETTINGS::Tile::Ice;
        break;

    case 5:
        type = SETTINGS::Tile::Water;
        break;
    }
}

bool Tile::getRemoved() const
{
    return removed;
}

void Tile::setRemoved(bool value)
{
    removed = value;
}

sf::IntRect Tile::getGlobalRect() const
{
    sf::Vector2i pos = getPosition();
    sf::IntRect r = utils::toIntRect(sprite.getGlobalBounds());

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
