#ifndef ENTITY_H
#define ENTITY_H

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
    Entity(sf::Vector2f _position);
    virtual ~Entity();
    virtual void update(const sf::Time &elapsedTime) = 0;

    float getSpeed() const;
    void setSpeed(float value);
    sf::Vector2f adaptPosition();

private:
    sf::Vector2f position;
    float speed;
};
} //namespace BattleCity
#endif // ENTITY_H
