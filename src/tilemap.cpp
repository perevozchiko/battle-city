#include "include/tilemap.h"

TileMap::TileMap() :
Entity (gameTexture, {0, 0}, Conf::SizeTexture, {Conf::WindowWidth/2, 0})
{
    gameTexture.loadFromFile("resources/images/sprite.bmp");
}
