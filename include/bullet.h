#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

namespace BattleCity  {

class Bullet : public Entity
{
public:
    Bullet();
    Bullet(sf::Vector2i _position, SET::Direction _direction);

    SET::Direction getDirection() const;
    void setDirection(const SET::Direction &value);

    void update(const sf::Time& elapsedTime) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool getVisible() const;
    void setVisible(bool value);

    int getSpeed() const;
    void setSpeed(int value);

    sf::Vector2i getPosition() const;
    void setPosition(const sf::Vector2i &value);

private:
    SET::Direction direction;
    bool visible;
    sf::Vector2i position;
    int speed;
};
} //namespace BattleCity

#endif // BULLET_H
