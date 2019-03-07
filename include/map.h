#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Map
{
public:
    Map(Texture& _texture, int height, int width);
    Sprite& getSprite() {return sprite;}
    sf::String getTileMap() {return TileMap;}
    void update(Time elapsedTime);

private:
    Texture& texture;
    Sprite sprite;
    sf::String TileMap;
    const int mapHeight;
    const int mapWidth;

};

#endif // MAP_H
