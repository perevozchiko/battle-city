#ifndef HEADQUARTERS_H
#define HEADQUARTERS_H

#include "entity.h"

namespace BattleCity {

class Base : public Entity
{
public:
    Base(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2i position);
    void update(const sf::Time& elapsedTime) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Vector2i size;
    sf::Sprite sprite;
    bool removed{false};
};

} //namespace BattleCity
#endif // HEADQUARTERS_H
