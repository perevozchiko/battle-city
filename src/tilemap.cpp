#include "include/tilemap.h"

TileMap::TileMap(Conf::Tile _type) :
    Entity ({0, 272}, Conf::SizeTileMap, {0, 0}),
    type(_type)
{

}

void TileMap::update(const sf::Time &elapsedTime)
{

}
