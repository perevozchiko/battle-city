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
    Enemy();
    Enemy(const sf::Texture &texture, sf::Vector2i offset, sf::Vector2f position);

    void changeDirectionMoving();
    void update(const sf::Time& elapsedTime) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void adaptEnemyPosition();
    void setDirection(const SET::Direction &_direction);

    sf::Sprite getSprite() const;

private:
    sf::Vector2i size;
    sf::Sprite sprite;
    SET::Direction direction;
    //RandomGen random;
};
} //namespace BattleCity
#endif // ENEMY_H
