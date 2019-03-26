#include "entity.h"

namespace BattleCity {
Entity::Entity(sf::Vector2f _position) :
    position(_position),
    speed(0)
{
    setPosition(_position);
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

sf::Vector2f Entity::adaptPosition()
{
    sf::Vector2f position = getPosition();

    position.x = std::max(position.x, static_cast<float>(SET::SIZE_TILE_TANK.x/2));
    position.x = std::min(position.x, static_cast<float>(SET::WINDOW_WIDTH - SET::SIZE_TILE_TANK.x/2));

    position.y = std::max(position.y, static_cast<float>(SET::SIZE_TILE_TANK.y/2));
    position.y = std::min(position.y, static_cast<float>(SET::WINDOW_HEIGHT - SET::SIZE_TILE_TANK.y/2));

    return position;
}

} //namespace BattleCity
