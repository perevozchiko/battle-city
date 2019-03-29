#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

namespace BattleCity  {

class Bullet : public Entity
{
public:
    Bullet() = delete;
    Bullet(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2i position);

    SET::Direction getDirection() const;
    void setDirection(const SET::Direction &value);

    void update(const sf::Time& elapsedTime) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool getVisible() const;
    void setVisible(bool value);



private:
    sf::Sprite sprite;
    SET::Direction direction;
    sf::Vector2i size;
    bool visible;
};
} //namespace BattleCity

#endif // BULLET_H
