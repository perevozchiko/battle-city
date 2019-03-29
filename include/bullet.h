#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

namespace BattleCity  {

class Bullet : public Entity
{
public:
    Bullet() = default;
    Bullet(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2i position);
    ~Bullet() override;

    SET::Direction getDirection() const;
    void setDirection(const SET::Direction &value);
    sf::IntRect getGlobalRect() const;

    void update(const sf::Time& elapsedTime) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool getRemoved() const;
    void setRemoved(bool value);

private:
    sf::Sprite sprite;
    SET::Direction direction;
    sf::Vector2i size;
    bool removed{false};

};
} //namespace BattleCity

#endif // BULLET_H
