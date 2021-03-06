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
    Tile() = default;
    Tile(const sf::Texture &texture, sf::Vector2i _offset);
    ~Tile() override;

    void update(const sf::Time& elapsedTime) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::IntRect getGlobalRect() const;
    SETTINGS::TileType getType() const;
    void setType(const int &value);

    bool isAlive() const;
    void setForRemove();

private:
    sf::Sprite sprite;
    sf::Vector2i offset;
    sf::Vector2i size;
    SETTINGS::TileType type;
    bool life{true};
};

} //namespace BattleCity
#endif // TILEMAP_H
