#ifndef ENTITY_H
#define ENTITY_H

#include <cmath>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "set.h"
#include "utils.h"



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
    void setSpeed(const int &value);
    sf::Vector2i adaptPosition();
    sf::Vector2i getPosition() const;
    void setPosition(const sf::Vector2i &value);
    void setPosition(int x, int y);

    //для коллизий player и enemy
    bool getCollisionDetected() const;
    void setCollisionDetected(bool value);

private:
    sf::Vector2i position;
    int speed;
    bool collisionDetected {false};
};
} //namespace BattleCity
#endif // ENTITY_H
