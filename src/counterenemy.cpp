#include "counterenemy.h"


namespace BattleCity {


CounterEnemy::CounterEnemy(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2i position) :
    Entity(position),
    size({14,14})
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(offset, size));
    setObjectType(Entity::ObjectType::CounterEnemy);
}

void CounterEnemy::update(const sf::Time &elapsedTime)
{

}

void CounterEnemy::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(sprite, states);
}

sf::IntRect CounterEnemy::getGlobalRect() const
{

}

bool CounterEnemy::isAlive() const
{
    return life;
}

void CounterEnemy::setForRemove()
{
    life = false;
}

} //namespace BattleCity
