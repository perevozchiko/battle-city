#include "entity.h"

Entity::Entity(sf::Vector2i _offset, sf::Vector2i _size, sf::Vector2f _position) :
    offset(_offset),
    size(_size),
    position(_position)
{
    texture.loadFromFile("resources/images/sprite.bmp");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(offset.x, offset.y, size.x, size.y));
    sprite.setOrigin(size.x/2, size.y/2);
    sprite.setPosition(position);
}

Entity::~Entity()
{

}

sf::Vector2f Entity::getPosition() const
{
    return sprite.getPosition();
}

void Entity::setPosition(const sf::Vector2f &value)
{
    sprite.setPosition(value);
}

sf::Sprite& Entity::getSprite()
{
    return sprite;
}

sf::Vector2i Entity::getOffset() const
{
    return offset;
}

void Entity::setOffset(const sf::Vector2i &value)
{
    offset = value;
}

void Entity::setSprite(const sf::Sprite &value)
{
    sprite = value;
}

sf::Vector2i Entity::getSize() const
{
    return size;
}
