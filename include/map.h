#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
using namespace sf;

class map
{
public:
    map(int height, int width);

private:
    const int mapHeight;
    const int mapWidth;
};

#endif // MAP_H
