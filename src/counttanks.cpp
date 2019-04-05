#include "counttanks.h"


namespace BattleCity {


CountTanks::CountTanks(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2i position) :
    Entity(position),
    size({14,14})
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(offset, size));
}

void CountTanks::update(const sf::Time &elapsedTime)
{

}

void CountTanks::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}

bool CountTanks::getRemoved() const
{
    return removed;
}

void CountTanks::setRemoved(bool value)
{
    removed = value;
}

} //namespace BattleCity
