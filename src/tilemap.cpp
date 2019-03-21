#include "include/tilemap.h"

TileMap::TileMap() :
    Entity({0,288}, {16,16}, {0,0})
{

}

TileMap::TileMap(Conf::Tile _type) :
    type(_type)
{

}

void TileMap::update(const sf::Time &elapsedTime)
{

}


sf::Vector2i TileMap::setOffset()
{
    switch (type)
    {
    case Conf::Tile::Ice:
        return {0, 288};

    case Conf::Tile::Brick:
        return {0, 256};

    case Conf::Tile::Shrub:
        return {0, 304};

    case Conf::Tile::Water:
        return {0, 320};

    case Conf::Tile::Concrete:
        return {0, 272};
    }
}
