#include "entity.h"
#include <iostream>



Entity::Entity(sf::Texture& _texture, sf::Vector2i _offset, sf::Vector2i _size, sf::Vector2f _position) :
    texture(_texture),
    offset(_offset),
    size(_size),
    position(_position)
{
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

sf::Sprite Entity::getSprite() const
{
    return sprite;
}

void Entity::update(const sf::Time elapsedTime)
{

}

sf::Vector2i Entity::getSize() const
{
    return size;
}
