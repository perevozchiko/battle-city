#ifndef TILEMAP_H
#define TILEMAP_H
#include "entity.h"

class TileMap : public Entity
{
public:
    TileMap();
    TileMap(Conf::Tile _type);
    void update(const sf::Time& elapsedTime) override;
    sf::Vector2i setOffset();

private:
    Conf::Tile type;
};

#endif // TILEMAP_H
