#ifndef TANK_H
#define TANK_H

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "set.h"

namespace BattleCity {

/** @class
 *
 */
class Entity
{
public:
    Entity();
    Entity(sf::Vector2i _offset, sf::Vector2i _size);
    virtual ~Entity();

    void setPosition(const sf::Vector2f &value);
    sf::Vector2f getPosition() const;


    //    void setOffset(const sf::Vector2i &value);
    //    sf::Vector2i getOffset() const;


    //    void setPosition(const sf::Vector2i &value);


    //    sf::Vector2i getSize() const;

    virtual void update(const sf::Time &elapsedTime) = 0;

    //    sf::Texture getTexture() const;
    //   void setTextureRectange(sf::IntRect value);

    sf::Sprite& getSprite();

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2i offset;
    sf::Vector2i size;
};
} //namespace BattleCity
#endif // TANK_H
