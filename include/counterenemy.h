#ifndef COUNTERENEMY_H
#define COUNTERENEMY_H

#include "entity.h"

namespace BattleCity {

class CounterEnemy : public Entity
{
public:
    CounterEnemy(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2i position);
    void update(const sf::Time& elapsedTime) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::IntRect getGlobalRect() const;


    bool isAlive() const;
    void setForRemove();


private:
    sf::Vector2i size;
    sf::Sprite sprite;
    bool life{true};
};
} //namespace BattleCity
#endif // COUNTERENEMY
