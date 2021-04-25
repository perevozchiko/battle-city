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
    Enemy(const sf::Texture &texture, SETTINGS::EnemyType _type, SETTINGS::PositionEnemy startPosition);
    ~Enemy() override;

    void changeDirectionMoving();
    void update(const sf::Time& elapsedTime) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void adaptEnemyPosition();
    void setDirection(const SETTINGS::Direction &_direction);
    sf::IntRect getGlobalRect() const;

    //sf::Vector2f getMovement();

    sf::Sprite getSprite() const;

    SETTINGS::Direction getDirection() const;

    void setTexture(const sf::Texture &texture, sf::Vector2i offset);

    bool isAlive() const;
    void setForRemove();
    sf::Vector2i getStartPosition(SETTINGS::PositionEnemy _startPosition);
    sf::Vector2i getOffset(SETTINGS::EnemyType &value);

    static int getCount();

    void setMovement();
    sf::Vector2f getMovement() const;

private:
    sf::Vector2i size;
    sf::Sprite sprite;
    SETTINGS::Direction direction;
    bool life{true};
    static int count;
    SETTINGS::EnemyType type;
    sf::Vector2f movement {0.f, 0.f};
    //RandomGen random;
};
} //namespace BattleCity
#endif // ENEMY_H
