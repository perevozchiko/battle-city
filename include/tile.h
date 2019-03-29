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

    void update(const sf::Time& elapsedTime) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::IntRect getGlobalRect() const;
    SET::Tile getType() const;
    void setType(const int &value);

    bool getRemoved() const;
    void setRemoved(bool value);

private:
    sf::Sprite sprite;
    sf::Vector2i offset;
    sf::Vector2i size;
    SET::Tile type;
    bool removed{false};
};

} //namespace BattleCity
#endif // TILEMAP_H
