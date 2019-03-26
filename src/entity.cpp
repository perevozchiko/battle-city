#include "entity.h"

namespace BattleCity {
Entity::Entity(sf::Vector2f _position) :
    position(_position),
    speed(0)
{

}

Entity::~Entity()
{

}

float Entity::getSpeed() const
{
    return speed;
}

void Entity::setSpeed(float value)
{
    speed = value;
}





} //namespace BattleCity
