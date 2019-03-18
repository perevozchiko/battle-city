#include "include/tilemap.h"

TileMap::TileMap() :
    Entity ({0, 0}, Conf::SizeTexture, {Conf::WindowWidth/2, 0})
{
}
