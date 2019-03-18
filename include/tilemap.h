#ifndef TILEMAP_H
#define TILEMAP_H
#include "entity.h"

class TileMap : public Entity
{
public:
    TileMap(Conf::Tile _type);
    void update(const sf::Time& elapsedTime) override;

private:
   // sf::Texture tile;
    Conf::Tile type;
};

#endif // TILEMAP_H
