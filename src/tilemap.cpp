#include "include/tilemap.h"

TileMap::TileMap(Conf::Tile _type) :
    Entity ({0, 0}, Conf::SizeTileMap, {0, 0}),
    type(_type)
{
   getSprite().setTextureRect(sf::IntRect(0, 272, 16, 16));
   getSprite().setOrigin(8, 8);
   getSprite().setPosition(250, 250);
}

void TileMap::update(const sf::Time &elapsedTime)
{

}
