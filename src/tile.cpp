#include "tile.h"

namespace BattleCity {

Tile::Tile(const sf::Texture &texture, sf::Vector2i _offset) :
    Entity ({0,0}),
    offset(_offset),
    size(SETTINGS::SIZE_TILE_MAP, SETTINGS::SIZE_TILE_MAP),
    type(SETTINGS::TileType::Empty)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(offset, size));
    setObjectType(Entity::ObjectType::Tile);
}

Tile::~Tile()
{

}

void Tile::update(const sf::Time &elapsedTime)
{
  auto a = elapsedTime;

}


SETTINGS::TileType Tile::getType() const
{
    return type;
}

void Tile::setType(const int &value)
{
    switch (value)
    {
    case 0:
        type = SETTINGS::TileType::Empty;
        break;

    case 1:
        type = SETTINGS::TileType::Brick;
        break;

    case 2:
        type = SETTINGS::TileType::Concrete;
        break;

    case 3:
        type = SETTINGS::TileType::Shrub;
        break;

    case 4:
        type = SETTINGS::TileType::Ice;
        break;

    case 5:
        type = SETTINGS::TileType::Water;
        break;
    }
}

bool Tile::isAlive() const
{
    return life;
}

void Tile::setForRemoved()
{
    life = false;
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
