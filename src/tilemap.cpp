#include "include/tilemap.h"

namespace BattleCity {

TileMap::TileMap()
{

}

TileMap::TileMap(sf::Vector2i offset) :
    Entity(offset, SET::SIZE_TILE_MAP)
{

}

//TileMap::TileMap(SET::Tile _type) :
//    type(_type)
//{

//}

void TileMap::update(const sf::Time &elapsedTime)
{

}


//sf::Vector2i TileMap::setOffset()
//{
//    switch (type)
//    {
//    case SET::Tile::Ice:
//        return {0, 288};

//    case SET::Tile::Brick:
//        return {0, 256};

//    case SET::Tile::Shrub:
//        return {0, 304};

//    case SET::Tile::Water:
//        return {0, 320};

//    case SET::Tile::Concrete:
//        return {0, 272};
//    }
//}
} //namespace BattleCity
