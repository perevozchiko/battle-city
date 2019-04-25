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

    SETTINGS::Direction getDirection() const;
    void setDirection(const SETTINGS::Direction &value);
    sf::IntRect getGlobalRect() const;

    void update(const sf::Time& elapsedTime) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool isAlive() const;
    void setForRemove();

    SETTINGS::bulletType getType() const;
    void setType(const SETTINGS::bulletType &value);

    sf::Vector2f getMovement() const;
    void setMovement();

private:
    sf::Sprite sprite;
    SETTINGS::Direction direction;
    sf::Vector2i size;
    bool life{true};
    SETTINGS::bulletType type;
    sf::Vector2f movement;


};
} //namespace BattleCity

#endif // BULLET_H
