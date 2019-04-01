#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include "randomgen.h"

namespace BattleCity {

/** @class
 *
 */
class Enemy : public Entity
{
public:
    Enemy();
    Enemy(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2i position);
    ~Enemy() override;

    void changeDirectionMoving();
    void update(const sf::Time& elapsedTime) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void adaptEnemyPosition();
    void setDirection(const SETTINGS::Direction &_direction);
    sf::IntRect getGlobalRect() const;

    sf::Sprite getSprite() const;

    SETTINGS::Direction getDirection() const;

    void setTexture(const sf::Texture &texture, sf::Vector2i offset);

    int getRemoved() const;
    void setRemoved(int value);

private:
    sf::Vector2i size;
    sf::Sprite sprite;
    SETTINGS::Direction direction;
    int removed{false};
    //RandomGen random;
};
} //namespace BattleCity
#endif // ENEMY_H
