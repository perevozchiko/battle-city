#ifndef TILEMAP_H
#define TILEMAP_H
#include "entity.h"

class TileMap : public Entity
{
public:
    TileMap();
private:
    sf::Texture gameTexture;
};

#endif // TILEMAP_H
