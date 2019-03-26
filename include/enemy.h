#ifndef ENEMY_H
#define ENEMY_H
#include "tank.h"
#include "randomgen.h"
#include "utils.h"
namespace BattleCity {

/** @class
 *
 */
class Enemy : public Entity
{
public:
    Enemy() = delete;
    Enemy(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2f position);

    void changeDirectionMoving();
    void update(const sf::Time& elapsedTime) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void adaptEnemyPosition();

    SET::Direction getDirection() const;
    void setDirection(const SET::Direction &value);

private:
    sf::Vector2i size;
    sf::Sprite sprite;
    SET::Direction direction;
    RandomGen random;
};
} //namespace BattleCity
#endif // ENEMY_H
