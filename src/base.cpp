#include "base.h"

namespace BattleCity {

Base::Base(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2i position) :
    Entity(position),
    size(SETTINGS::SIZE_TILE_BASE)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(offset, size));
}

void Base::update(const sf::Time &elapsedTime)
{
    if(removed)
    {
        sprite.setTextureRect(sf::IntRect(SETTINGS::BASE_REMOVED_OFFSET, SETTINGS::SIZE_TILE_BASE));
        removed = true;
    }
}

void Base::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}

bool Base::getRemoved() const
{
    return removed;
}

void Base::setRemoved(bool value)
{
    removed = value;
}

sf::Sprite& Base::getSprite()
{
    return sprite;
}

void Base::setSprite(const sf::Sprite &value)
{
    sprite = value;
}

sf::IntRect Base::getGlobalRect() const
{
    sf::Vector2i pos = getPosition();
    sf::IntRect r = utils::toIntRect(sprite.getGlobalBounds());

    r.left = pos.x;
    r.top = pos.y;
    return r;
}




} //namespace BattleCity
