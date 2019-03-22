#include "entity.h"

namespace BattleCity {
Entity::Entity()
{

}

Entity::~Entity()
{

}

Entity::Entity(sf::Vector2i _offset, sf::Vector2i _size) :
    offset(_offset),
    size(_size)
{
    texture.loadFromFile(SET::PATH_IMAGES);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(offset.x, offset.y, size.x, size.y));
   //sprite.setOrigin(size.x/2, size.y/2);
}

//sf::Vector2f Entity::getPosition() const
//{
//    return sprite.getPosition();
//}

//void Entity::setPosition(const sf::Vector2f &value)
//{
//    sprite.setPosition(value);
//}

void Entity::setPosition(const sf::Vector2f &value)
{
    sprite.setPosition(value);
}

sf::Sprite& Entity::getSprite()
{
    return sprite;
}



//sf::Vector2i Entity::getOffset() const
//{
//    return offset;
//}

//void Entity::setOffset(const sf::Vector2i &value)
//{
//    offset = value;
//}

//void Entity::setSprite(const sf::Sprite &value)
//{
//    sprite = value;
//}

//sf::Vector2i Entity::getSize() const
//{
//    return size;
//}

//sf::Texture Entity::getTexture() const
//{
//    return texture;
//}

//void Entity::setTextureRectange(sf::IntRect value)
//{
//    sprite.setTextureRect(value);
//}
} //namespace BattleCity
