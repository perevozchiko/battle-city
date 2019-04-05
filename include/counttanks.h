#ifndef COUNTTANKS_H
#define COUNTTANKS_H

#include "entity.h"

namespace BattleCity {

class CountTanks : public Entity
{
public:
    CountTanks(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2i position);
    void update(const sf::Time& elapsedTime) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool getRemoved() const;
    void setRemoved(bool value);

private:
    sf::Vector2i size;
    sf::Sprite sprite;
    bool removed{false};
};
} //namespace BattleCity
#endif // COUNTTANKS_H
