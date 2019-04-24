#ifndef BASE_H
#define BASE_H

#include "entity.h"

namespace BattleCity {

class Staff : public Entity
{
public:
    Staff(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2i position);
    void update(const sf::Time& elapsedTime) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool getRemoved() const;
    void setRemoved(bool value);

    sf::Sprite& getSprite();
    void setSprite(const sf::Sprite &value);

    sf::IntRect getGlobalRect() const;

private:
    sf::Vector2i size;
    sf::Sprite sprite;
    bool removed{false};
};

} //namespace BattleCity
#endif // BASE_H
