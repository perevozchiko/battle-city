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

}

void Base::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}

} //namespace BattleCity
