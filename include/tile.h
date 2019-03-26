#ifndef TILEMAP_H
#define TILEMAP_H

#include "entity.h"


namespace BattleCity {

/** @class
 *
 */
class Tile : public Entity
{
public:
    Tile() = delete;
    Tile(const sf::Texture &texture, sf::Vector2i _offset);

    void update(const sf::Time& elapsedTime) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::FloatRect getGlobalRect() const;
    SET::Tile getType() const;
    void setType(const int &value);

private:
    sf::Sprite sprite;
    sf::Vector2i offset;
    sf::Vector2i size;
    SET::Tile type;
};

} //namespace BattleCity
#endif // TILEMAP_H
