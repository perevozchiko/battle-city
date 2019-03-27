#ifndef ENTITY_H
#define ENTITY_H

#include <cmath>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "set.h"

namespace BattleCity {

/** @class
 *
 */
class Entity : public sf::Transformable, public sf::Drawable
{
public:
    Entity();
    Entity(sf::Vector2i _position);
    virtual ~Entity();
    virtual void update(const sf::Time &elapsedTime) = 0;

    int getSpeed() const;
    void setSpeed(int value);
    sf::Vector2i adaptPosition();
    sf::Vector2i getPosition() const;
    void setPosition(const sf::Vector2i &value);
    void setPosition(int x, int y);

private:
    sf::Vector2i position;
    int speed;
};
} //namespace BattleCity
#endif // ENTITY_H
