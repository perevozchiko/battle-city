#include "entity.h"

namespace BattleCity {

Entity::Entity()
{

}

Entity::Entity(sf::Vector2i _position) :
    position(_position),
    speed(0)
{
    setPosition(_position.x, _position.y);
}

Entity::~Entity()
{

}

int Entity::getSpeed() const
{
    return speed;
}

void Entity::setSpeed(const int &value)
{
    speed = value;
}

sf::Vector2i Entity::adaptPosition()
{
    sf::Vector2i position = getPosition();

    position.x = std::max(position.x, SETTINGS::SIZE_TILE_PLAYER.x/2 + SETTINGS::SIZE_TILE_MAP * 2);
    position.x = std::min(position.x, SETTINGS::WINDOW_WIDTH - SETTINGS::SIZE_TILE_PLAYER.x/2 - SETTINGS::SIZE_TILE_MAP * 4);
    position.y = std::max(position.y, SETTINGS::SIZE_TILE_PLAYER.y/2 + SETTINGS::SIZE_TILE_MAP);
    position.y = std::min(position.y, SETTINGS::WINDOW_HEIGHT - SETTINGS::SIZE_TILE_PLAYER.y/2 - SETTINGS::SIZE_TILE_MAP);

    return position;
}

sf::Vector2i Entity::getPosition() const
{
    sf::Vector2i pos = {static_cast<int>(std::round(sf::Transformable::getPosition().x)),
                        static_cast<int>(std::round(sf::Transformable::getPosition().y))};
    return pos;
}

void Entity::setPosition(const sf::Vector2i &value)
{
    sf::Transformable::setPosition(static_cast<float>(value.x), static_cast<float>(value.y));
}

void Entity::setPosition(int x, int y)
{
    sf::Transformable::setPosition(static_cast<float>(x), static_cast<float>(y));
}

bool Entity::getCollisionDetected() const
{
    return collisionDetected;
}

void Entity::setCollisionDetected(bool value)
{
    collisionDetected = value;
}

SETTINGS::ObjectType Entity::getObjectType() const
{
    return objectType;
}

void Entity::setObjectType(const SETTINGS::ObjectType &value)
{
    objectType = value;
}
} //namespace BattleCity
