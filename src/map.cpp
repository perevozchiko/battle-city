#include "include/map.h"

Map::Map(Texture& _texture, int height, int width) :
    texture(_texture),
    mapHeight(height),
    mapWidth(width)
{
    sf::String TileMap[25] = {
        "0000000000000000000000000000000000000000",
            "0                                      0",
            "0   s                                  0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0000000000000000000000000000000000000000",
    };
}

void Map::update(Time elapsedTime)
{

}
