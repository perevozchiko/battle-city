#ifndef TILEMAP_H
#define TILEMAP_H

#include "entity.h"


namespace BattleCity {

/** @class
 *
 */
class Tile
{
public:
    Tile() = delete;

    Tile(sf::Vector2i _offset, const sf::Texture &texture);

    void update(const sf::Time& elapsedTime);
    //    sf::Vector2i setOffset();

    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f &value);

    sf::Sprite getSprite() const;
    void setSprite(const sf::Sprite &value);



    std::vector<sf::String> getMap() const;


    SET::Tile getType() const;
    void setType(const int &value);

private:
    sf::Sprite sprite;
    sf::Vector2i offset;
    sf::Vector2i size;
    sf::Vector2f position;
    SET::Tile type;
};

} //namespace BattleCity
#endif // TILEMAP_H
