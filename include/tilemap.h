#ifndef TILEMAP_H
#define TILEMAP_H

#include "entity.h"

namespace BattleCity {

/** @class
 *
 */
class TileMap : public Entity
{
public:
    TileMap();
    TileMap(sf::Vector2i _offset);

    void update(const sf::Time& elapsedTime) override;
//    sf::Vector2i setOffset();

private:
//    SET::Tile type;
};
} //namespace BattleCity
#endif // TILEMAP_H
