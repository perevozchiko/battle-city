#include "staff.h"

namespace BattleCity {

Staff::Staff(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2i position) :
    Entity(position),
    size(SETTINGS::SIZE_TILE_BASE)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(offset, size));
    setObjectType(Entity::ObjectType::Staff);
}

void Staff::update(const sf::Time &elapsedTime)
{
    if(!life)
    {
        sprite.setTextureRect(sf::IntRect(SETTINGS::BASE_REMOVED_OFFSET, SETTINGS::SIZE_TILE_BASE));
        life = true;
    }
}

void Staff::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}

bool Staff::isAlive() const
{
    return life;
}

void Staff::setForRemove()
{
    life = false;
}

sf::Sprite& Staff::getSprite()
{
    return sprite;
}

void Staff::setSprite(const sf::Sprite &value)
{
    sprite = value;
}

sf::IntRect Staff::getGlobalRect() const
{
    sf::Vector2i pos = getPosition();
    sf::IntRect r = utils::toIntRect(sprite.getGlobalBounds());

    r.left = pos.x;
    r.top = pos.y;
    return r;
}




} //namespace BattleCity
