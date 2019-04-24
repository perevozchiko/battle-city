#include "counterenemy.h"


namespace BattleCity {


CounterEnemy::CounterEnemy(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2i position) :
    Entity(position),
    size({14,14})
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(offset, size));
    setObjectType(SETTINGS::ObjectType::CounterEnemy);
}

void CounterEnemy::update(const sf::Time &elapsedTime)
{

}

void CounterEnemy::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}

bool CounterEnemy::getRemoved() const
{
    return removed;
}

void CounterEnemy::setRemoved(bool value)
{
    removed = value;
}

} //namespace BattleCity